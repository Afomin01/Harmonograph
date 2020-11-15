#pragma once

#include <QtWidgets>
#include "Harmonograph.h"
#include "settings.h"

class FlexPainter {
public:
	FlexPainter(FlexSettings* settings);
	QImage getImage(int width, int height, int zoom);

private:
	Harmonograph* harmonograph;
	QColor backgroundColor;
	bool useTwoColors = true;
	bool useAntialiasing = false;
	int penWidth = 1;
	QColor firstColor;
	QColor secondColor;
};

