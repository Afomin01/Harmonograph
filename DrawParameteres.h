#pragma once
#include <QColor>

class DrawParameters{
public:
	bool useTwoColors = true;
	bool useAntiAliasing = false;
	int penWidth = 1;
	float zoom = 0.25;
	
	QColor firstColor = Qt::blue;
	QColor secondColor = Qt::red;
	QColor backgroundColor = Qt::white;
};