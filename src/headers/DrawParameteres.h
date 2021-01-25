#pragma once
#include <QColor>


enum class DrawModes {
	linesMode,
	pointsMode
};

class DrawParameters{
public:
	bool useTwoColors = true;
	bool useAntiAliasing = true;
	DrawModes drawMode = DrawModes::linesMode;
	int penWidth = 1;
	float zoom = 0.25;
	float timeStep = 0.01;
	
	QColor primaryColor = Qt::blue;
	QColor secondColor = Qt::red;
	QColor backgroundColor = Qt::white;
};


