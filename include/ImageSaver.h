#pragma once

#include <Qwidget>
#include <QFileDialog>
#include "Harmonograph.h"
#include "json.hpp"
#include "ImagePainter.h"
#include <fstream>
#include "Pendulum.h"
#include <QTextStream>

using json = nlohmann::json;

class ImageSaver {
public:
	ImageSaver();
	void saveImage(Harmonograph* harmonograph, QString filename, ImagePainter* imagePainter);
	void saveParametersToFile(QString filename, Harmonograph* harmonograph);
	Harmonograph* loadParametersFromFile(QString filename);

	int getSaveWidth() {
		return saveImageWidth;
	}
	int getSaveHeight() {
		return saveImageHeight;
	}
	
private:
	int saveImageWidth = 7680;//2560
	int saveImageHeight = 4320;//1440
};

