#pragma once

#include <QtWidgets>
#include <QFileDialog>
#include "Harmonograph.h"
#include "json.hpp"
#include <fstream>
#include "Pendulum.h"
#include <QTextStream>
#include "PendulumDimension.h"
#include "settings.h"

using json = nlohmann::json;

class HarmonographSaver {
public:
	HarmonographSaver();
	void saveImage(Harmonograph* harmonograph, ImageSettings* settings);
	void saveParametersToFile(QString filename, Harmonograph* harmonograph);
	Harmonograph* loadParametersFromFile(QString filename);
};

