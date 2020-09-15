#pragma once

#include <Qwidget>
#include <QFileDialog>
#include "Harmonograph.h"
#include "json.hpp"
#include <fstream>
#include "Pendulum.h"

using json = nlohmann::json;

class ImageSaver {
public:
	ImageSaver();
	void saveImage(QString filename, QImage image);
	void saveParametersToFile(QString filename, Harmonograph* harmonograph);
	Harmonograph* loadParametersFromFile(QString filename);

	int getSaveWidth() {
		return saveImageWidth;
	}
	int getSaveHeight() {
		return saveImageHeight;
	}
	
private:
	int saveImageWidth = 2560;
	int saveImageHeight = 1440;
};

