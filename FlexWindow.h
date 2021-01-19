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
#include "HarmonographOpenGLWidget.h"

class FlexWindow : public QMainWindow
{
	Q_OBJECT

public:

	FlexWindow(FlexSettings* settings, QWidget* parent = Q_NULLPTR);

protected:
	virtual void closeEvent(QCloseEvent* event);
private:
	Ui::FlexWindow ui;
	Harmonograph* flexGraph;
	QTimer* flexTimer;
	HarmonographOpenGLWidget* gl;
	HarmonographManager* manager;

	float firstFreq = 2;
	float secondFreq = 2;
	float flexSpeedChangeFactor = 0.005;
	std::vector<float> xFlexStartValues;
	std::vector<float> yFlexStartValues;
	std::vector<float> xSpeedValues;
	std::vector<float> ySpeedValues;
	int FPSLimit = 60;

	double boundedRandDouble(double fMin, double fMax) {
		double f = (double)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
	}

private slots:
	void frequencyFlex();
	void phaseFlex();
	void maximize();
	void increaseFlexSpeed();
	void decreaseFlexSpeed();
};
