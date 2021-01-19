#pragma once
#include <QtWidgets>
#include "Harmonograph.h"
#include "FlexModesEnum.h"
#include "DrawParameteres.h"

class FlexSettings {
public:
	Harmonograph* flexGraph = nullptr;
	FlexModes flexBaseMode = FlexModes::phaseBased;
	int FPSLimit = 60;
	DrawParameters parameters;
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
