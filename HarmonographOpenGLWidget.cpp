#include "HarmonographOpenGLWidget.h"
#include <qdebug.h>

HarmonographOpenGLWidget::HarmonographOpenGLWidget(QWidget* parent, HarmonographManager* manager){
	this->manager = manager;
}

HarmonographOpenGLWidget::~HarmonographOpenGLWidget(){
}

void HarmonographOpenGLWidget::wheelEvent(QWheelEvent* event){
	QPoint numDegrees = event->angleDelta() / 8;

	float yDegrees = numDegrees.y()/2000.0;

	const float temp = zoom + yDegrees;
	if (temp > minZoom && temp < maxZoom) {
		zoom += yDegrees;
	}
	this->update();
}

void HarmonographOpenGLWidget::mouseMoveEvent(QMouseEvent* event){
	if (isMousePressed) {
		int dx = previousX - static_cast<int>(event->globalX());
		int dy = previousY - static_cast<int>(event->globalY());

		float dfX = ((dx / stepPhaseX) * piTwo);
		float dfY = ((dy / stepPhaseY) * piTwo);

		previousX = event->globalX();
		previousY = event->globalY();

		manager->rotateXY(dfX, dfY);
	}
	this->update();
}

void HarmonographOpenGLWidget::mousePressEvent(QMouseEvent* event){
	isMousePressed = true;
	previousX = event->globalX();
	previousY = event->globalY();
	this->setCursor(Qt::ClosedHandCursor);
	this->update();
}

void HarmonographOpenGLWidget::mouseReleaseEvent(QMouseEvent* event){
	isMousePressed = false;
	this->setCursor(Qt::OpenHandCursor);
	this->update();
}

void HarmonographOpenGLWidget::initializeGL() {
	glClearColor(1, 1, 1, 1);
	glLineWidth(penWidth);
	glEnable(GL_MULTISAMPLE);
}

void HarmonographOpenGLWidget::resizeGL(int w, int h){
	qInfo() << w << " " << h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	float aspect = (float)w / (float)h;
	glOrtho(-aspect, aspect, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void HarmonographOpenGLWidget::paintGL(){
	glPointSize(3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_LINE_STRIP);//GL_POINTS  GL_LINE_STRIP

	float xCurrent = 0;
	float yCurrent = 0;

	int stepCount = (int)(255 / 1e-02) + 10;
	float stepR = ((float)(secondColor.redF() - firstColor.redF()) / stepCount);
	float stepG = ((float)(secondColor.greenF() - firstColor.greenF()) / stepCount);
	float stepB = ((float)(secondColor.blueF() - firstColor.blueF()) / stepCount);
	int i = 1;

	for (float t = 0; t < 255; t += 1e-02) {
		glColor3f(firstColor.redF() + stepR * i, firstColor.greenF() + stepG * i, firstColor.blueF() + stepB * i);

		xCurrent = (manager->getCoordinateByTime(Dimension::x, t) * zoom);
		yCurrent = (manager->getCoordinateByTime(Dimension::y, t) * zoom);

		glVertex3f(xCurrent, yCurrent, 0);
		i++;
	}
	glEnd();
}
