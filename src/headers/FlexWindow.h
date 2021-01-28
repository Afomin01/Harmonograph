/*
 *   Copyright 2020-2021 Artem Bakin and Dmitriy Kuperstein
 *
 *   This file is part of Harmonograph.
 *
 *   Harmonograph is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Harmonograph is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Harmonograph.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <QMainWindow>
#include <QtWidgets>
#include <ui_FlexWindow.h>
#include "Harmonograph.h"
#include <QThreadPool>
#include <QTimer>
#include <cmath>
#include <random>
#include <time.h>
#include "HarmonographOpenGLWidget.h"
#include "SaveImageDialog.h"
#include "settings.h"

class FlexWindow : public QMainWindow
{
	Q_OBJECT

public:

	FlexWindow(FlexSettings* settings, QWidget* parent = Q_NULLPTR);
	~FlexWindow();

protected:
	virtual void closeEvent(QCloseEvent* event);
private:
	Ui::FlexWindow ui;
	Harmonograph* flexGraph;
	QTimer* flexTimer;
	HarmonographOpenGLWidget* gl;
	HarmonographManager* manager;
	QAction* maximizeAction, * incSpeedAction, * decSpeedAction, * pauseAction, * saveImageAction;

	SaveImageDialog* saveImageDialog = new SaveImageDialog(this);

	float firstFreq = 2;
	float secondFreq = 2;
	float flexSpeedChangeFactor = 0.002;
	std::vector<float> xFlexStartValues;
	std::vector<float> yFlexStartValues;
	std::vector<float> xSpeedValues;
	std::vector<float> ySpeedValues;
	int FPSLimit = 60;
	bool isFlexPaused = false;

	double boundedRandDouble(double fMin, double fMax) {
		double f = (double)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
	}

private slots:
	void frequencyFlex();
	void phaseFlex();
	void maximizeWindow();
	void increaseFlexSpeed();
	void decreaseFlexSpeed();
	void pauseFlex();
	void saveImageToFile();
};
