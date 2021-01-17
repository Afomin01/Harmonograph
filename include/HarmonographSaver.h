#pragma once

#include <Qwidget>
#include <QFileDialog>
#include "Harmonograph.h"
#include "json.hpp"
#include "ImagePainter.h"
#include <fstream>
#include "Pendulum.h"
#include <QTextStream>
#include "PendulumDimension.h"

using json = nlohmann::json;

class HarmonographSaver {
public:
	HarmonographSaver();
	void saveImage(Harmonograph* harmonograph, QString filename, ImagePainter* imagePainter);
	void saveParametersToFile(QString filename, Harmonograph* harmonograph);
	Harmonograph* loadParametersFromFile(QString filename);

	int saveImageWidth = 7680;//2560
	int saveImageHeight = 4320;//1440
	
private:
};

