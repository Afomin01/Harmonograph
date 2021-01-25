#pragma once
#include <qopenglwidget.h>
#include "HarmonographManager.h"
#include "settings.h"
#include "GL/glut.h"


class HarmonographOpenGLWidget : public QOpenGLWidget {
public:
    bool isMousePressed = false;
    int previousX = 0;
    int previousY = 0;
    float stepPhaseX = 90;
    float stepPhaseY = 90;
    const float piTwo = static_cast<float>(2 * atan(1) * 4);
    float minZoom = 0.1, maxZoom = 0.75;

    HarmonographManager* manager = nullptr;

    HarmonographOpenGLWidget(QWidget* parent = nullptr, HarmonographManager* manager = nullptr);
    ~HarmonographOpenGLWidget();

    void setEnableAA(bool isEnabled);

protected:
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

