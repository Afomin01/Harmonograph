#include "FlexWindow.h"
#include "FlexSettings.h"
#include <QDebug>

FlexWindow::FlexWindow(FlexSettings* settings, QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);
	this->flexGraph = settings->flexGraph;
	if (flexGraph == NULL) flexGraph = new Harmonograph(3);
	scene = new QGraphicsScene(this);
	ui.graphicsView->setScene(scene);

	this->setAttribute(Qt::WA_DeleteOnClose);

	this->firstColor = settings->firstColor;
	this->secondColor = settings->secondColor;
	this->backgoundColor = settings->backgroundColor;
	this->useTwoColors = settings->useTwoColors;

	flexTimer = new QTimer(this);
	flexTimer->setInterval((int)((1.0/settings->FPSLimit)*1000));

	flexPainter = new FlexPainter(settings);

	QAction* max = new QAction(this);
	max->setShortcut(Qt::Key_F11);

	connect(max, SIGNAL(triggered()), this, SLOT(maximize()));
	this->addAction(max);

	connect(ui.graphicsView, SIGNAL(zoomChanged(int)), this, SLOT(changeZoom(int)));
	srand(time(NULL));

	if (flexGraph->isStar) {
		firstFreq = (flexGraph->frequencyPoint /
			(flexGraph->firstRatioValue + flexGraph->secondRatioValue))
			* flexGraph->firstRatioValue;

		secondFreq = (flexGraph->frequencyPoint /
			(flexGraph->firstRatioValue + flexGraph->secondRatioValue))
			* flexGraph->secondRatioValue;
	}

	if (settings->flexBaseMode == 1) {
		for (Pendulum p : flexGraph->getPendulums()) {
			ySpeedValues.push_back(boundedRandDouble(0.005, 0.01));
			xSpeedValues.push_back(boundedRandDouble(0.005, 0.01));
		}

		connect(flexTimer, SIGNAL(timeout()), this, SLOT(phaseFlex()));
	}
	else {
		for (Pendulum p : flexGraph->getPendulums()) {
			xFlexStartValues.push_back(asin(10 * p.xFrequencyNoise));
			yFlexStartValues.push_back(acos(10 * p.yFrequencyNoise));

			ySpeedValues.push_back(boundedRandDouble(0.0005, 0.001));
			xSpeedValues.push_back(boundedRandDouble(0.0005, 0.001));
		}

		connect(flexTimer, SIGNAL(timeout()), this, SLOT(frequencyFlex()));
	}

	connect(ui.graphicsView, SIGNAL(rotateScene(float, float)), this, SLOT(rotateSceneXY(float, float)));

	flexTimer->start();
	delete settings;
}

void FlexWindow::closeEvent(QCloseEvent* event) {
	flexTimer->stop();
	delete flexGraph;
	delete scene;
	delete flexTimer;
}

void FlexWindow::maximize() {
	if (this->isFullScreen()) {
		this->showNormal();
		maxZoom = 200;
		zoom = 125;
		width = ui.graphicsView->width();
		height = ui.graphicsView->height();
	}
	else {
		this->showFullScreen();
		maxZoom = (int)(200 / (1280.0 / ui.graphicsView->width()));
		width = ui.graphicsView->width();
		height = ui.graphicsView->height();
	}
}

void FlexWindow::changeZoom(int value) {
	float temp = zoom + value;
	if (temp > minZoom && temp < maxZoom) {
		zoom += value;
	}
}


void FlexWindow::frequencyFlex() {
	scene->clear();
	scene->addItem(new QGraphicsPixmapItem(QPixmap::fromImage(flexPainter->getImage(width,height,zoom))));

	for (int i = 0; i < flexGraph->getNumOfPendulums();i++) {
		xFlexStartValues.at(i) += xSpeedValues.at(i);
		flexGraph->getPendulums().at(i)->xFreq = 
			(flexGraph->isStar ? 
			(i == 0 ? firstFreq : secondFreq)
			: flexGraph->frequencyPoint)
			+ sin(xFlexStartValues.at(i)) / 10.0;

		yFlexStartValues.at(i) += ySpeedValues.at(i);
		flexGraph->getPendulums().at(i)->yFreq =
			(flexGraph->isStar ?
			(i == 0 ? firstFreq : secondFreq)
			: flexGraph->frequencyPoint)
			+ cos(yFlexStartValues.at(i)) / 10.0;
	}
}

void FlexWindow::phaseFlex() {
	scene->clear();
	scene->addItem(new QGraphicsPixmapItem(QPixmap::fromImage(flexPainter->getImage(width, height, zoom))));

	for (int i = 0; i < flexGraph->getNumOfPendulums(); i++) {
		flexGraph->getPendulums().at(i)->changeXPhase(xSpeedValues.at(i));

		flexGraph->getPendulums().at(i)->changeYPhase(ySpeedValues.at(i));
	}
}

void FlexWindow::rotateSceneXY(float x, float y) {
	flexGraph->rotateXY(x, y);
}