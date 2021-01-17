#include "ImageSaver.h"
#include <QRunnable>
#include <QThreadPool>

class SaveImageTask : public QRunnable {
public:
	SaveImageTask(Harmonograph* harmonograph, ImageSaver* imageSaver, QString filename, ImagePainter* imagePainter) {
		this->imageSaver = imageSaver;
		this->filename = filename;
		this->harmonograph = harmonograph;
		this->imagePainter = imagePainter;
	}

	ImageSaver* imageSaver;
	QString filename;
	Harmonograph* harmonograph;
	ImagePainter* imagePainter;

	void run() override {
		QImage imageToSave = imagePainter->getImageToSave(
			harmonograph,
			imageSaver->saveImageWidth,
			imageSaver->saveImageHeight);

		imageToSave.save(filename);

		delete imagePainter;
		delete harmonograph;
	}
};

ImageSaver::ImageSaver() {
	//load settings logic
}

void ImageSaver::saveImage(Harmonograph* harmonograph, QString filename, ImagePainter* imagePainter) {
	SaveImageTask* task = new SaveImageTask(harmonograph, this, filename, imagePainter);
	QThreadPool::globalInstance()->start(task);
}

void ImageSaver::saveParametersToFile(QString filename, Harmonograph* harmonograph) {
	json j;
	j["numOfPendulums"] = harmonograph->getNumOfPendulums();
	j["frequencyRatio"] = std::to_string(harmonograph->firstRatioValue) + ":" + std::to_string(harmonograph->secondRatioValue);
	j["frequencyPoint"] = harmonograph->frequencyPoint;
	j["isStar"] = harmonograph->isStar;
	j["isCircle"] = harmonograph->isCircle;

	std::vector<Pendulum*> pendulums = harmonograph->getPundlumsCopy();

	for (int i = 0; i < pendulums.size(); i++) {
		std::vector<PendulumDemension*> demensions = pendulums.at(i)->getDimensionsCopy();
		
		for (int k = 0; k < demensions.size(); k++) {
			PendulumDemension* d = demensions.at(k);

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


Harmonograph* ImageSaver::loadParametersFromFile(QString filename) {
	if (!filename.isEmpty()) {
		try {

			QFile qFile(filename);
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

			for (int i = 0; i < numOfPendulums; i++) {
				json pendulumArray = j["pendulums"];

				std::vector<PendulumDemension*> demensions;

				for (auto p : pendulumArray) {
					PendulumDemension* demension = new PendulumDemension(
						p["amplitude"],
						p["frequency"],
						p["phase"],
						p["dumping"],
						p["frequencyNoise"]);
					demensions.push_back(demension);
				}

				Pendulum* pendulum = new Pendulum(demensions);
			}


			//last version before refactoring. needed to upgrade previous save files

			//for (int i = 0; i < numOfPendulums; i++) {
			//	Pendulum* Pendulum = new Pendulum(j["pendulums"][i]["xDamp"],
			//		j["pendulums"][i]["xPhase"], 
			//		j["pendulums"][i]["xFreq"], 
			//		j["pendulums"][i]["xFreqNoise"],
			//		j["pendulums"][i]["xAmpl"],
			//		j["pendulums"][i]["yDamp"], 
			//		j["pendulums"][i]["yPhase"],
			//		j["pendulums"][i]["yFreq"],
			//		j["pendulums"][i]["yFreqNoise"],
			//		j["pendulums"][i]["yAmpl"]);		

			//	pendulums.push_back(Pendulum);
			//}

			qFile.close();

			Harmonograph* harmonograph = new Harmonograph(pendulums, firstRatioValue, secondRatioValue, isStar, isCircle, frequencyPoint);
			return harmonograph;
		}
		catch (...) {
			return nullptr;
			//file.close();
		}

	}
	return nullptr;
}
