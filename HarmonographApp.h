#pragma once

#include <QtWidgets/QMainWindow>
#include "Harmonograph.h"
#include <QGraphicsPixmapItem>
#include <ui_HarmonographApp.h>
#include <QElapsedTimer>
#include "Harmonograph.h"
#include <cstdlib>

class HarmonographApp : public QMainWindow
{
    Q_OBJECT

public:
    HarmonographApp(QWidget *parent = Q_NULLPTR);

private:
    Harmonograph *harmonograph;
    
    int const drawImgWidth = 1280;
    int const drawImgHeight = 720;
    float zoom = 100;

    Ui::HarmonographAppClass ui;

    QGraphicsScene* scene;
    QImage* image;
    QPainter* painter;
    QPen pen;

    void drawImage();
private slots:
    void updateImage();
    void autoRotate();
};
