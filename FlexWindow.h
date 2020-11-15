#pragma once

#include <QMainWindow>
#include <QtWidgets>
#include <ui_FlexWindow.h>
#include <ui_FlexWindow.h>
#include "Harmonograph.h"
#include <QThreadPool>
#include <QTimer>
#include "FlexPainter.h"
#include <cmath>
#include <random>
#include <time.h>

class FlexWindow : public QMainWindow
{
	Q_OBJECT

public:

	FlexWindow(FlexSettings* settings, QWidget* parent = Q_NULLPTR);

protected:
	virtual void closeEvent(QCloseEvent* event);
private:
	Ui::FlexWindow ui;
	QGraphicsScene* scene;
	Harmonograph* flexGraph;
	QTimer* flexTimer;

	float zoom = 125;
	float minZoom = 75;
	float maxZoom = 200;
	bool useTwoColors = true;
	int width = 1280;
	int height = 720;
	float firstFreq = 2;
	float secondFreq = 2;
	std::vector<float> xFlexStartValues;
	std::vector<float> yFlexStartValues;
	std::vector<float> xSpeedValues;
	std::vector<float> ySpeedValues;
	FlexPainter* flexPainter;
	QColor firstColor = Qt::blue;
	QColor secondColor = Qt::red;
	QColor backgoundColor = Qt::white;

	double boundedRandDouble(double fMin, double fMax) {
		double f = (double)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
	}

private slots:
	void frequencyFlex();
	void phaseFlex();
	void maximize();
	void changeZoom(int value);

	void rotateSceneXY(float x, float y);
};
