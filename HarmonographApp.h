#pragma once

#include <QTimer>
#include <QtWidgets/QMainWindow>
#include "Harmonograph.h"
#include <QGraphicsPixmapItem>
#include <ui_HarmonographApp.h>
#include <QElapsedTimer>
#include "Harmonograph.h"
#include <cstdlib>
#include "HarmonographManager.h"

class HarmonographApp : public QMainWindow
{
    Q_OBJECT

public:
    HarmonographApp(QWidget *parent = Q_NULLPTR);

private:
    HarmonographManager* manager;
    
    int const drawImgWidth = 1280;
    int const drawImgHeight = 720;
    float zoom = 100;

    Ui::HarmonographAppClass ui;

    QGraphicsScene* scene;
    QTimer* autoRotationTimer;

    void redrawImage();

private slots:
    void updateImage();
    void autoRotate();
    void autoRotationTimerTimeout();
    void saveImage();
};
