#pragma once
#include <qopenglwidget.h>
#include "HarmonographManager.h"
#include<GL/glut.h>

class OpenGLCustomWidget : public QOpenGLWidget {
public:
    QColor firstColor = Qt::blue;
    QColor secondColor = Qt::red;
    QColor backgroundColor = Qt::white;

    int penWidth = 1;
    float zoom = 0.25;
    bool useTwoColors = true;

    HarmonographManager* manager = nullptr;
	
    OpenGLCustomWidget(QWidget* parent = nullptr, HarmonographManager* manager = nullptr);
    ~OpenGLCustomWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
	
};

