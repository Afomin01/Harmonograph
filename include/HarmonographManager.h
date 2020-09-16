#pragma once
#include <QtWidgets>
#include "Harmonograph.h"
#include "ImagePainter.h"
#include "ImageSaver.h"

class HarmonographManager{
public:
	HarmonographManager();

	QGraphicsPixmapItem* getRenderedGraphicsItem();
	void updateRandomValues();
	void changeXAxisRotation(float radians);
	void saveCurrentImage(QString filename);
	void saveParametersToFile(QString filename);
	void loadParametersFromFile(QString filename);
	void changeZoom(float value);
	void changeFirstColor(QColor color);
	void changeSecondColor(QColor color);
	void enableTwoColorMode(bool isEnabled);




private:
	Harmonograph* harmonograph;
	ImagePainter* imagePainter;
	ImageSaver* imageSaver;
};

