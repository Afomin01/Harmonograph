#include "HarmonographSaver.h"
#include <QRunnable>
#include <QThreadPool>

class SaveImageTask : public QRunnable {
public:
	SaveImageTask(Harmonograph* harmonograph, QString filename, DrawParameters parameters, int width, int height) {
		this->filename = filename;
		this->harmonograph = harmonograph;
		this->parameters = parameters;
		imageToSave = new QImage(width, height, QImage::Format_ARGB32);
		this->width = width;
		this->height = height;
	}

	QString filename;
	Harmonograph* harmonograph;
	DrawParameters parameters;
	QImage* imageToSave;

	int width = 1280;
	int height = 720;

	void run() override {
		float const borderPercentage = 0.03;
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

		int stepCount = (int)(255 / 1e-04) + 10;
		float stepR = ((float)(parameters.secondColor.red() - parameters.primaryColor.red()) / stepCount);
		float stepG = ((float)(parameters.secondColor.green() - parameters.primaryColor.green()) / stepCount);
		float stepB = ((float)(parameters.secondColor.blue() - parameters.primaryColor.blue()) / stepCount);

		if (width == height) {
			float maxX = 0, maxY = 0, maxTotal = 0;

			for (float t = 0; t < 225; t += 1e-02) {
				float x = harmonograph->getCoordinateByTime(Dimension::x, t);
				float y = harmonograph->getCoordinateByTime(Dimension::y, t);
				if (x > maxX) maxX = x;
				if (y > maxY) maxY = y;
			}

			maxTotal = maxX > maxY ? maxX : maxY;

			saveZoom = (width / 2) / maxTotal;
			saveZoom -= saveZoom * borderPercentage;
		}

		int i = 1;

		float xLast = (harmonograph->getCoordinateByTime(Dimension::x, 0) * saveZoom) + widthAdd;
		float yLast = -(harmonograph->getCoordinateByTime(Dimension::y, 0) * saveZoom) + heightAdd;

		float xCurrent = 0;
		float yCurrent = 0;

		for (float t = 1e-04; t < 255; t += 1e-04) {

			savePen.setColor(QColor(parameters.primaryColor.red() + stepR * i, parameters.primaryColor.green() + stepG * i, parameters.primaryColor.blue() + stepB * i, 255));
			savePainter->setPen(savePen);
			xCurrent = (harmonograph->getCoordinateByTime(Dimension::x, t) * saveZoom) + widthAdd;
			yCurrent = -(harmonograph->getCoordinateByTime(Dimension::y, t) * saveZoom) + heightAdd;

			savePainter->drawLine(xLast, yLast, xCurrent, yCurrent);

			xLast = xCurrent;
			yLast = yCurrent;
			i++;
		}
		delete savePainter;		

		imageToSave->save(filename);

		delete imageToSave;
		delete harmonograph;
	}
};

HarmonographSaver::HarmonographSaver() {
	//load settings logic
}

void HarmonographSaver::saveImage(Harmonograph* harmonograph, QString filename, DrawParameters parameters, int width, int height) {
	SaveImageTask* task = new SaveImageTask(harmonograph, filename, parameters, width, height);
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
