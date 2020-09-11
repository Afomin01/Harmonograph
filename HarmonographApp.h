#pragma once

#include <QtWidgets/QMainWindow>
#include "Harmonograph.h"
#include <QGraphicsPixmapItem>
#include <ui_HarmonographApp.h>

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

    void drawImage() {

        harmonograph->update();
        painter->fillRect(0, 0, drawImgWidth, drawImgHeight, Qt::white);

        float xLast = (harmonograph->getX(0) * zoom) + (drawImgWidth / 2);
        float yLast = (harmonograph->getY(0) * zoom) + (drawImgHeight / 2);
        float xCurrent = 0;
        float yCurrent = 0;

        for (float t = 1e-02; t < 255; t += 1e-02) {

            xCurrent = (harmonograph->getX(t) * zoom) + (drawImgWidth / 2);
            yCurrent = (harmonograph->getY(t) * zoom) + (drawImgHeight / 2);

            painter->drawLine(xLast, yLast, xCurrent, yCurrent);

            xLast = xCurrent;
            yLast = yCurrent;
        }
        scene->clear();
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
        scene->addItem(item);

    }
private slots:
    void updateImage();
};
