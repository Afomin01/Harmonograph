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

		imageToSave->save(filename);

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
	json j;
	j["numOfPendulums"] = harmonograph->getNumOfPendulums();
	j["frequencyRatio"] = std::to_string(harmonograph->firstRatioValue) + ":" + std::to_string(harmonograph->secondRatioValue);
	j["frequencyPoint"] = harmonograph->frequencyPoint;
	j["isStar"] = harmonograph->isStar;
	j["isCircle"] = harmonograph->isCircle;

	std::vector<Pendulum*> pendulums = harmonograph->getPundlumsCopy();

	for (int i = 0; i < pendulums.size(); i++) {
		std::vector<PendulumDimension*> demensions = pendulums.at(i)->getDimensionsCopy();
		
		for (int k = 0; k < demensions.size(); k++) {
			PendulumDimension* d = demensions.at(k);

			j["pendulums"][i][k]["amplitude"] = d->amplitude;
			j["pendulums"][i][k]["dumping"] = d->dumping;
			j["pendulums"][i][k]["frequency"] = d->frequency;
			j["pendulums"][i][k]["frequencyNoise"] = d->frequencyNoise;
			j["pendulums"][i][k]["phase"] = d->phase;
		}
	}

	QFile file(filename);
	file.open(QIODevice::ReadWrite);
	QTextStream out(&file);
	out << QString::fromStdString(j.dump(4)) << endl;

	file.close();

	delete harmonograph;
}


Harmonograph* HarmonographSaver::loadParametersFromFile(QString filename) {
	if (!filename.isEmpty()) {
		QFile qFile(filename);
		try {
			qFile.open(QIODevice::ReadWrite);
			QTextStream in(&qFile);
			QString fileString(in.readAll());

			json j = json::parse(fileString.toStdString());
			int numOfPendulums = j["numOfPendulums"];
			std::string ratio = j["frequencyRatio"];
			int firstRatioValue = std::stoi(ratio.substr(0, ratio.find(':')));
			int secondRatioValue = std::stoi(ratio.substr(ratio.find(':')+1, ratio.size()-1));
			float frequencyPoint = j["frequencyPoint"];
			bool isStar = j["isStar"];
			bool isCircle = j["isCircle"];

			std::vector<Pendulum*> pendulums;
			json pendulumArray = j["pendulums"];

			for (int i = 0; i < numOfPendulums; i++) {
				auto dimensionsArray = pendulumArray[i];

				std::vector<PendulumDimension*> dimensions;

				for (auto d : dimensionsArray) {
					PendulumDimension* dim = new PendulumDimension(
						d["amplitude"],
						d["frequency"],
						d["phase"],
						d["dumping"],
						d["frequencyNoise"]);
					dimensions.push_back(dim);
				}

				Pendulum* pendulum = new Pendulum(dimensions);
				pendulums.push_back(pendulum);
			}

			qFile.close();

			Harmonograph* harmonograph = new Harmonograph(pendulums, firstRatioValue, secondRatioValue, isStar, isCircle, frequencyPoint);
			return harmonograph;
		}
		catch (...) {
			qFile.close();
			return nullptr;
		}

	}
	return nullptr;
}
