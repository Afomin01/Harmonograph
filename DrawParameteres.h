#pragma once
#include <QColor>


enum class DrawModes {
	linesMode,
	pointsMode
};

class DrawParameters{
public:
	bool useTwoColors = true;
	bool useAntiAliasing = false;
	DrawModes drawMode = DrawModes::linesMode;
	int penWidth = 1;
	float zoom = 0.25;
	
	QColor firstColor = Qt::blue;
	QColor secondColor = Qt::red;
	QColor backgroundColor = Qt::white;
};


