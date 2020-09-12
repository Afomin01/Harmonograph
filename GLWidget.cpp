#include "GLWidget.h"

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {
    harmonograph = new Harmonograph(3);
}

void GLWidget::initializeGL() {
	glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(1);      
}
void GLWidget::resizeGL(int w, int h) {

}
void GLWidget::paintGL() {
    draw();
}
void GLWidget::updateImageGL() {

    paintGL();
    update();
}
