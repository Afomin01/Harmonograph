#pragma once

#include <QtWidgets>
#include "Harmonograph.h"

class FlexPainter {
public:
	FlexPainter(Harmonograph* harmonograph, QColor backgroundColor, bool useTwoColors, QColor firstColor, QColor secondColor, int penWidth, bool useAntialiasing);
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

