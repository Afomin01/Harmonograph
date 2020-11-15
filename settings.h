#pragma once
#include <QtWidgets>
#include "Harmonograph.h"

class FlexSettings {
public:
	Harmonograph* flexGraph = nullptr;
	int flexBaseMode = 1;
	bool useAntialiasing = false;
	int penWidth = 1;
	int FPSLimit = 60;
	QColor firstColor = Qt::blue;
	QColor secondColor = Qt::red;
	bool useTwoColors = true;
	QColor backgroundColor = Qt::white;
};

class ImageSettings {
public:
	QString filename;
	int penWidth;
	bool useAntialiasing;
	bool useSquareImage;
	int saveWidth;
	int saveHeight;
	bool transpBack;
};
