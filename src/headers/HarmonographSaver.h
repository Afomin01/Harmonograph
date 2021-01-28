#pragma once

#include <QtWidgets>
#include "Harmonograph.h"
#include "Pendulum.h"
#include "PendulumDimension.h"
#include "settings.h"

class HarmonographSaver {
public:
	HarmonographSaver();
	void saveImage(Harmonograph* harmonograph, ImageSettings* settings);
	void saveParametersToFile(QString filename, Harmonograph* harmonograph);
	Harmonograph* loadParametersFromFile(QString filename);
};

