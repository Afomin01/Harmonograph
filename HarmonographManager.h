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


private:
	Harmonograph* harmonograph;
	ImagePainter* imagePainter;
	ImageSaver* imageSaver;

};

