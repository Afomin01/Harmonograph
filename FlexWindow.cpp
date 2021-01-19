#include "FlexWindow.h"
#include "settings.h"
#include <QDebug>


FlexWindow::FlexWindow(FlexSettings* settings, QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);

	this->flexGraph = settings->flexGraph;
	
	if (flexGraph == NULL) flexGraph = new Harmonograph(3);
	manager = new HarmonographManager(flexGraph);

	auto gridLayout = dynamic_cast<QGridLayout*>(ui.centralWidget->layout());
	gl = new HarmonographOpenGLWidget(this, manager);

	if(settings->useAntialiasing){
		gl->setEnableAA(true);
	}
	
	gridLayout->addWidget(gl, 0, 0);

	this->setAttribute(Qt::WA_DeleteOnClose);

	manager->setFirstColor(settings->firstColor);
	manager->setSecondColor(settings->secondColor);
	manager->setBackgroundColor(settings->backgroundColor);
	manager->enableTwoColorMode(settings->useTwoColors);
    manager->setPenWidth(settings->penWidth);
	manager->enableAntiAliasing(settings->useAntialiasing);

	if (settings->flexBaseMode == FlexModes::frequencyBased)
		flexSpeedChangeFactor = flexSpeedChangeFactor / 30.0;

	flexTimer = new QTimer(this);
	FPSLimit = settings->FPSLimit;
	flexTimer->setInterval((int)((1.0/settings->FPSLimit)*1000));

	QAction* max = new QAction(this);
	max->setShortcut(Qt::Key_F11);
	QAction* incSpeed = new QAction(this);
	incSpeed->setShortcut(Qt::Key_Equal);
	QAction* decSpeed = new QAction(this);
	decSpeed->setShortcut(Qt::Key_Minus);

	connect(max, SIGNAL(triggered()), this, SLOT(maximize()));
	connect(incSpeed, SIGNAL(triggered()), this, SLOT(increaseFlexSpeed()));
	connect(decSpeed, SIGNAL(triggered()), this, SLOT(decreaseFlexSpeed()));
	
	this->addAction(max);
	this->addAction(incSpeed);
	this->addAction(decSpeed);

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

void FlexWindow::closeEvent(QCloseEvent* event) {
	flexTimer->stop();
	delete flexGraph;
	delete gl;
	delete manager;
	delete flexTimer;
}

void FlexWindow::maximize() {
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