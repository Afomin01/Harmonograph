#pragma once

#include <Qwidget>
#include <QtWidgets>
#include <QFileDialog>
#include "Harmonograph.h"
#include "json.hpp"
#include <fstream>
#include "Pendulum.h"
#include <QTextStream>
#include "PendulumDimension.h"
#include "DrawParameteres.h"

using json = nlohmann::json;

class HarmonographSaver {
public:
	HarmonographSaver();
	void saveImage(Harmonograph* harmonograph, QString filename, DrawParameters parameters, int width, int height);
	void saveParametersToFile(QString filename, Harmonograph* harmonograph);
	Harmonograph* loadParametersFromFile(QString filename);
};

