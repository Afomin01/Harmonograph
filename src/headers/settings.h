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
	DrawParameters parameters;
	QString filename = "";
	bool useSquareImage = false;
	int borderPercentage = 3;
	int saveWidth = 1920;
	int saveHeight = 1080;
};

class ColorTemplate {
public:
	ColorTemplate(QColor primary, QColor secondary, QColor background);
	ColorTemplate() = default;

	QColor primaryColor = Qt::blue;
	QColor secondaryColor = Qt::red;
	QColor backgroundColor = Qt::white;
};

class NamedColorTemplate {
public:
	NamedColorTemplate(long long id, QString filename, QString name, ColorTemplate colorTemplate);

	long long id = 0;
	QString filename = "";
	QString name = "";
	ColorTemplate colorTemplate;
};
