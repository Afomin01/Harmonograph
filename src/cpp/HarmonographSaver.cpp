/*
 *   Copyright 2020-2021 Artem Bakin and Dmitriy Kuperstein
 *
 *   This file is part of Harmonograph.
 *
 *   Harmonograph is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Harmonograph is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Harmonograph.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "HarmonographSaver.h"
#include <QRunnable>
#include <QThreadPool>

class SaveImageTask : public QRunnable {
public:
	QString filename;
	Harmonograph* harmonograph;
	DrawParameters parameters;
	QImage* imageToSave;

	int width = 1280;
	int height = 720;
	float borderPercentage = 0.03;
	
	SaveImageTask(Harmonograph* harmonograph, ImageSettings* settings) {
		this->filename = settings->filename;
		this->harmonograph = harmonograph;
		this->parameters = settings->parameters;
		this->width = settings->saveWidth;
		this->height = settings->saveHeight;
		this->borderPercentage = settings->borderPercentage/100.0;

		imageToSave = new QImage(width, height, QImage::Format_ARGB32);
		delete settings;
	}
	
	void run() override {
		int const maxT = 255;
		float const tStep = 1e-04;
		QPainter* savePainter = new QPainter(imageToSave);
		QPen savePen;
		savePen.setCapStyle(Qt::RoundCap);

		if (parameters.useAntiAliasing) savePainter->setRenderHint(QPainter::Antialiasing, true);
		savePen.setColor(Qt::black);
		savePen.setWidth(parameters.penWidth);
		savePainter->setPen(savePen);

		savePainter->fillRect(0, 0, width, height, parameters.backgroundColor);

		float widthAdd = width / 2;
		float heightAdd = height / 2;

		int saveZoom = (int)((parameters.zoom * 500) / ((1280 * 1.0) / width));

		float stepR = 0, stepG = 0, stepB = 0;

		if (parameters.useTwoColors) {
			int stepCount = 0;
			if (parameters.drawMode == DrawModes::linesMode) stepCount = (int)(maxT / tStep) + 10;
			else stepCount = (int)(maxT / parameters.timeStep) + 10;

			stepR = ((float)(parameters.secondColor.red() - parameters.primaryColor.red()) / stepCount);
			stepG = ((float)(parameters.secondColor.green() - parameters.primaryColor.green()) / stepCount);
			stepB = ((float)(parameters.secondColor.blue() - parameters.primaryColor.blue()) / stepCount);
		}

		
		float maxX = 0, maxY = 0, xZoom = 0, yZoom = 0;

		for (float t = 0; t < maxT; t += 1e-02) {
			float x = abs(harmonograph->getCoordinateByTime(Dimension::x, t));
			float y = abs(harmonograph->getCoordinateByTime(Dimension::y, t));
			if (x > maxX) maxX = x;
			if (y > maxY) maxY = y;
		}

		xZoom = (width / 2.0) / maxX;
		yZoom = (height / 2.0) / maxY;

		saveZoom = xZoom > yZoom ? yZoom : xZoom;
		saveZoom -= saveZoom * borderPercentage;


		int i = 1;
		if (parameters.drawMode == DrawModes::linesMode) {

			float xLast = (harmonograph->getCoordinateByTime(Dimension::x, 0) * saveZoom) + widthAdd, xCurrent = 0;
			float yLast = -(harmonograph->getCoordinateByTime(Dimension::y, 0) * saveZoom) + heightAdd, yCurrent = 0;

			for (float t = tStep; t < maxT; t += tStep) {

				savePen.setColor(QColor(parameters.primaryColor.red() + stepR * i, parameters.primaryColor.green() + stepG * i, parameters.primaryColor.blue() + stepB * i, 255));
				savePainter->setPen(savePen);
				xCurrent = (harmonograph->getCoordinateByTime(Dimension::x, t) * saveZoom) + widthAdd;
				yCurrent = -(harmonograph->getCoordinateByTime(Dimension::y, t) * saveZoom) + heightAdd;

				savePainter->drawLine(xLast, yLast, xCurrent, yCurrent);

				xLast = xCurrent;
				yLast = yCurrent;
				i++;
			}

		}
		else {
			for (float t = 0; t < maxT; t += parameters.timeStep) {
				savePen.setColor(QColor(parameters.primaryColor.red() + stepR * i, parameters.primaryColor.green() + stepG * i, parameters.primaryColor.blue() + stepB * i, 255));
				savePainter->setPen(savePen);

				savePainter->drawPoint((harmonograph->getCoordinateByTime(Dimension::x, t) * saveZoom) + widthAdd, -(harmonograph->getCoordinateByTime(Dimension::y, t) * saveZoom) + heightAdd);

				i++;
			}
		}

		imageToSave->save(filename, "PNG");

		delete savePainter;
		delete imageToSave;
		delete harmonograph;
	}
};

HarmonographSaver::HarmonographSaver() {
	//load settings logic
}

void HarmonographSaver::saveImage(Harmonograph* harmonograph, ImageSettings* settings) {
	SaveImageTask* task = new SaveImageTask(harmonograph, settings);
	QThreadPool::globalInstance()->start(task);
}

void HarmonographSaver::saveParametersToFile(QString filename, Harmonograph* harmonograph) {
	QFile jsonFile(filename);

	QJsonDocument document = QJsonDocument();
	QJsonObject root = QJsonObject();
	QJsonArray pendulumsArray = QJsonArray();

	std::vector<Pendulum*> pendulums = harmonograph->getPundlumsCopy();

	for (int i = 0; i < pendulums.size();i++) {
		std::vector<PendulumDimension*> dimensions = pendulums.at(i)->getDimensionsCopy();

		QJsonArray dimensionsArray = QJsonArray();
		
		for (int j = 0; j < dimensions.size();j++) {

			PendulumDimension* dim = dimensions.at(j);

			QJsonObject dimObject = QJsonObject();

			dimObject.insert("amplitude", dim->amplitude);
			dimObject.insert("dumping", dim->dumping);
			dimObject.insert("frequency", dim->frequency);
			dimObject.insert("frequencyNoise", dim->frequencyNoise);
			dimObject.insert("phase", dim->phase);

			dimensionsArray.insert(j, dimObject);
		}

		pendulumsArray.insert(i, dimensionsArray);
	}

	try {
		jsonFile.open(QIODevice::WriteOnly);

		root.insert("frequencyPoint", QJsonValue(harmonograph->frequencyPoint));
		root.insert("frequencyRatio", QJsonValue(QString::fromStdString(std::to_string(harmonograph->firstRatioValue) + ":" + std::to_string(harmonograph->secondRatioValue))));
		root.insert("isStar", QJsonValue(harmonograph->isStar));
		root.insert("isCircle", QJsonValue(harmonograph->isCircle));
		root.insert("pendulums", pendulumsArray);
		document.setObject(root);

		jsonFile.write(QJsonDocument(document).toJson(QJsonDocument::Indented));
	}
	catch (...) {}

	jsonFile.close();

	delete harmonograph;
}


Harmonograph* HarmonographSaver::loadParametersFromFile(QString filename) {
	if (!filename.isEmpty()) {
		QFile jsonFile(filename);
		try {
			jsonFile.open(QIODevice::ReadOnly);

			QByteArray saveData = jsonFile.readAll();
			QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
			QJsonObject root = jsonDocument.object();

			std::string ratio = root.value("frequencyRatio").toString().toStdString();
			int firstRatioValue = std::stoi(ratio.substr(0, ratio.find(':')));
			int secondRatioValue = std::stoi(ratio.substr(ratio.find(':') + 1, ratio.size() - 1));
			
			float frequencyPoint = root.value("frequencyPoint").toDouble();
			bool isStar = root.value("isStar").toBool();
			bool isCircle = root.value("isCircle").toBool();

			std::vector<Pendulum*> pendulums;
			QJsonArray pendulumArray = root.value("pendulums").toArray();

			for (auto dimArr : pendulumArray) {
				QJsonArray dimensionsArray = dimArr.toArray();

				std::vector<PendulumDimension*> dimensions;

				for (auto d : dimensionsArray) {
					PendulumDimension* dim = new PendulumDimension(
						d.toObject().value("amplitude").toDouble(),
						d.toObject().value("frequency").toDouble(),
						d.toObject().value("phase").toDouble(),
						d.toObject().value("dumping").toDouble(),
						d.toObject().value("frequencyNoise").toDouble());
					dimensions.push_back(dim);
				}

				Pendulum* pendulum = new Pendulum(dimensions);
				pendulums.push_back(pendulum);
			}

			Harmonograph* harmonograph = new Harmonograph(pendulums, firstRatioValue, secondRatioValue, isStar, isCircle, frequencyPoint);
			return harmonograph;
		}
		catch (...) {
			jsonFile.close();
			return nullptr;
		}
	}
	return nullptr;

	
}
