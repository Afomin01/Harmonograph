#pragma once
#include <QtWidgets>
#include <QOpenGLWidget>
#include <gl/GLU.h>
#include <gl/GL.h>
#include "Harmonograph.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget* parent = 0);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    Harmonograph* harmonograph;

    int const drawImgWidth = 1280;
    int const drawImgHeight = 720;
    float zoom = 0.1;

    void draw() {
        harmonograph->update();

        float xLast = (harmonograph->getX(0) * zoom);
        float yLast = (harmonograph->getY(0) * zoom);
        float xCurrent = 0;
        float yCurrent = 0;

        glBegin(GL_LINES);
        glColor3d(0, 0, 0);
        for (float t = 1e-02; t < 255; t += 1e-02) {

            xCurrent = (harmonograph->getX(t) * zoom);
            yCurrent = (harmonograph->getY(t) * zoom);


            glVertex2f(xLast, yLast);
            glVertex2f(xCurrent, yCurrent);

            xLast = xCurrent;
            yLast = yCurrent;
        }
        glEnd();
    }
private slots:
    void updateImageGL();
};



