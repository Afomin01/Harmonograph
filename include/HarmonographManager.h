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

	void enableTwoColorMode(bool isEnabled);
	void changeFirstColor(QColor color);
	void changeSecondColor(QColor color);

	void ratioStateEnabled(bool isEnabled);
	void changeFirstRatioValue(int value);
	void changeSecondRatioValue(int value);

	void circleStateEnabled(bool isEnabled);

	void setFrequencyPoint(float freqPt);
	void setNumOfPendulums(int newNum);



private:
	Harmonograph* harmonograph;
	ImagePainter* imagePainter;
	ImageSaver* imageSaver;
};

