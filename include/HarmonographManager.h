#pragma once
#include <QtWidgets>
#include "Harmonograph.h"
#include "ImagePainter.h"
#include "ImageSaver.h"
#include <deque>

class HarmonographManager{
public:
	HarmonographManager();

	QGraphicsPixmapItem* getRenderedGraphicsItem();
	void updateRandomValues();

	void changeXAxisRotation(float radians);
	void rotateXY(float x, float y);

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

	void undoUpdate() {
		if (history.size() > 0) {
			Harmonograph* undoHarm = new Harmonograph(history.back());
			history.pop_back();

			delete harmonograph;

			harmonograph = undoHarm;
		}
	}

private:
	Harmonograph* harmonograph;
	ImagePainter* imagePainter;
	ImageSaver* imageSaver;
	std::deque<Harmonograph*> history;
};

