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

