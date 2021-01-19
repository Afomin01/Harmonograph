#include "OpenGLCustomWidget.h"
#include <QtOpenGL/QtOpenGL>
OpenGLCustomWidget::OpenGLCustomWidget(QWidget* parent, HarmonographManager* manager) : QOpenGLWidget(parent) {
	this->manager = manager;
}

OpenGLCustomWidget::~OpenGLCustomWidget() = default;

void OpenGLCustomWidget::initializeGL() {
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

void OpenGLCustomWidget::resizeGL(int w, int h) {
	
}

void OpenGLCustomWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_LINE_STRIP);
	
	float xCurrent = 0;
	float yCurrent = 0;
	float zCurrent = 0;

	int stepCount = (int)(255 / 1e-02) + 10;
	float stepR = ((float)(secondColor.redF() - firstColor.redF()) / stepCount);
	float stepG = ((float)(secondColor.greenF() - firstColor.greenF()) / stepCount);
	float stepB = ((float)(secondColor.blueF() - firstColor.blueF()) / stepCount);
	int i = 1;
	
	for (float t = 0; t < 255; t += 1e-02){
		glColor3f(firstColor.redF() + stepR * i, firstColor.greenF() + stepG * i, firstColor.blueF() + stepB * i);
		
		xCurrent = (manager->getCoordinateByTime(Dimension::x, t) * zoom);
		yCurrent = (manager->getCoordinateByTime(Dimension::y, t) * zoom);
		zCurrent = (manager->getCoordinateByTime(Dimension::y, t) * zoom);

		glVertex3f(xCurrent, yCurrent, zCurrent);
		i++;
	}
	glEnd();
}