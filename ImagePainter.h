#pragma once
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QtWidgets/QMainWindow>
#include <QPainter>
#include "Harmonograph.h"
#include <memory> 

class ImagePainter{
public:
    ImagePainter();
    QImage getImage(Harmonograph* harmonograph);
    QImage getImageToSave(Harmonograph* harmonograph, int width, int height);
private:
    int const drawImgWidth = 1280;
    int const drawImgHeight = 720;
    float zoom = 100;

    QImage* image;
    QPainter* painter;
    QPen pen;
};

