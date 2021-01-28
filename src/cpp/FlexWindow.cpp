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

#include "FlexWindow.h"


FlexWindow::FlexWindow(FlexSettings* settings, QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);

	DrawParameters parameters = settings->parameters;

	this->flexGraph = settings->flexGraph;
	
	if (flexGraph == NULL) flexGraph = new Harmonograph(3);
	manager = new HarmonographManager(flexGraph);
	manager->setDrawParameters(parameters);

	auto gridLayout = dynamic_cast<QGridLayout*>(ui.centralWidget->layout());
	gl = new HarmonographOpenGLWidget(this, manager);

	if(parameters.useAntiAliasing){
		gl->setEnableAA(true);
	}
	
	gridLayout->addWidget(gl, 0, 0);

	this->setAttribute(Qt::WA_DeleteOnClose);

	if (settings->flexBaseMode == FlexModes::frequencyBased)
		flexSpeedChangeFactor = flexSpeedChangeFactor / 30.0;
	if (settings->flexBaseMode == FlexModes::phaseBased)
		flexSpeedChangeFactor = flexSpeedChangeFactor / 2.0;

	flexTimer = new QTimer(this);
	FPSLimit = settings->FPSLimit;
	flexTimer->setInterval((int)((1.0/settings->FPSLimit)*1000));

	maximizeAction = new QAction(this);
	maximizeAction->setShortcut(Qt::Key_F11);
	
	incSpeedAction = new QAction(this);
	incSpeedAction->setShortcut(Qt::Key_Equal);
	
	decSpeedAction = new QAction(this);
	decSpeedAction->setShortcut(Qt::Key_Minus);
	
	pauseAction = new QAction(this);
	pauseAction->setShortcut(Qt::Key_P);

	saveImageAction = new QAction(this);
	saveImageAction->setShortcut(Qt::Key_S);

	this->addAction(maximizeAction);
	this->addAction(incSpeedAction);
	this->addAction(decSpeedAction);
	this->addAction(pauseAction);
	this->addAction(saveImageAction);

	connect(maximizeAction, SIGNAL(triggered()), this, SLOT(maximizeWindow()));
	connect(incSpeedAction, SIGNAL(triggered()), this, SLOT(increaseFlexSpeed()));
	connect(decSpeedAction, SIGNAL(triggered()), this, SLOT(decreaseFlexSpeed()));
	connect(pauseAction, SIGNAL(triggered()), this, SLOT(pauseFlex()));
	connect(saveImageAction, SIGNAL(triggered()), this, SLOT(saveImageToFile()));


	srand(time(NULL));

	if (flexGraph->isStar) {
		firstFreq = (flexGraph->frequencyPoint /
			(flexGraph->firstRatioValue + flexGraph->secondRatioValue))
			* flexGraph->firstRatioValue;

		secondFreq = (flexGraph->frequencyPoint /
			(flexGraph->firstRatioValue + flexGraph->secondRatioValue))
			* flexGraph->secondRatioValue;
	}

	float slowFactor = 30.0 / FPSLimit;

	if (settings->flexBaseMode == FlexModes::phaseBased) {
		for (Pendulum p : flexGraph->getPendulums()) {
			ySpeedValues.push_back(boundedRandDouble(0.005, 0.01)*slowFactor);
			xSpeedValues.push_back(boundedRandDouble(0.005, 0.01)*slowFactor);
		}

		connect(flexTimer, SIGNAL(timeout()), this, SLOT(phaseFlex()));
	}
	else {
		for (Pendulum p : flexGraph->getPendulums()) {
			xFlexStartValues.push_back(asin(10 * p.getEquationParameter(Dimension::x, EquationParameter::frequencyNoise)));
			yFlexStartValues.push_back(acos(10 * p.getEquationParameter(Dimension::y, EquationParameter::frequencyNoise)));

			ySpeedValues.push_back(boundedRandDouble(0.0005, 0.001)*slowFactor);
			xSpeedValues.push_back(boundedRandDouble(0.0005, 0.001)*slowFactor);
		}

		connect(flexTimer, SIGNAL(timeout()), this, SLOT(frequencyFlex()));
	}
	
	flexTimer->start();
	delete settings;
}

FlexWindow::~FlexWindow() {
	delete maximizeAction;
	delete incSpeedAction;
	delete decSpeedAction;
	delete pauseAction;
	delete flexTimer;
	delete gl;
}

void FlexWindow::closeEvent(QCloseEvent* event) {
	flexTimer->stop();
	delete manager;
}

void FlexWindow::maximizeWindow() {
	if (this->isFullScreen()) {
		this->showNormal();
	}
	else {
		this->showFullScreen();
	}
}


void FlexWindow::increaseFlexSpeed(){
	flexTimer->stop();
	for (int i = 0; i < xSpeedValues.size(); i++) {
		xSpeedValues.at(i) += flexSpeedChangeFactor;
		ySpeedValues.at(i) += flexSpeedChangeFactor;
	}
	flexTimer->start();
}

void FlexWindow::decreaseFlexSpeed(){
	flexTimer->stop();
	for (int i = 0; i < xSpeedValues.size(); i++) {
		xSpeedValues.at(i) -= flexSpeedChangeFactor;
		ySpeedValues.at(i) -= flexSpeedChangeFactor;
	}
	flexTimer->start();
}

void FlexWindow::pauseFlex() {
	if(isFlexPaused) {
		flexTimer->start();
	}else {
		flexTimer->stop();
	}
	isFlexPaused = !isFlexPaused;
}

void FlexWindow::saveImageToFile() {
	if(isFlexPaused) {
		int code = saveImageDialog->exec();

		if (code == 1) {
			QString fileName = QFileDialog::getSaveFileName(this,
				tr("Save Harmonograph Image"), "",
				tr("png image (*.png);;All Files (*)"));
			if (!fileName.isEmpty()) {
				ImageSettings* imageSettings = new ImageSettings();
				imageSettings->parameters = manager->getDrawParameters();

				imageSettings->filename = fileName;
				if (saveImageDialog->transpBack) imageSettings->parameters.backgroundColor = QColor(0, 0, 0, 0);
				imageSettings->parameters.penWidth = saveImageDialog->penWidth;
				imageSettings->parameters.useAntiAliasing = saveImageDialog->useAntialiasing;
				imageSettings->useSquareImage = saveImageDialog->useSquareImage;
				imageSettings->saveWidth = saveImageDialog->saveWidth;
				imageSettings->saveHeight = saveImageDialog->saveHeight;
				imageSettings->borderPercentage = saveImageDialog->borderPercentage;

				manager->saveCurrentImage(imageSettings);
			}
		}
	}
}

void FlexWindow::frequencyFlex() {
	gl->update();

	for (int i = 0; i < flexGraph->getNumOfPendulums();i++) {
		xFlexStartValues.at(i) += xSpeedValues.at(i);
		flexGraph->getPendulums().at(i)->setEquationParameter(
			Dimension::x,
			EquationParameter::frequency,
			(flexGraph->isStar ?
			(i == 0 ? firstFreq : secondFreq)
			: flexGraph->frequencyPoint)
			+ sin(xFlexStartValues.at(i)) / 10.0);

		yFlexStartValues.at(i) += ySpeedValues.at(i);
		flexGraph->getPendulums().at(i)->setEquationParameter(
			Dimension::y,
			EquationParameter::frequency,
			(flexGraph->isStar ?
			(i == 0 ? firstFreq : secondFreq)
			: flexGraph->frequencyPoint)
			+ cos(yFlexStartValues.at(i)) / 10.0);
	}
}

void FlexWindow::phaseFlex() {
	gl->update();

	for (int i = 0; i < flexGraph->getNumOfPendulums(); i++) {
		flexGraph->getPendulums().at(i)->changeDimensionEquationPhase(Dimension::x, xSpeedValues.at(i));

		flexGraph->getPendulums().at(i)->changeDimensionEquationPhase(Dimension::y, ySpeedValues.at(i));
	}
}