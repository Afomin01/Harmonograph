#pragma once
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QtWidgets/QMainWindow>
#include <QPainter>
#include "Harmonograph.h"
#include <memory> 

class ImagePainter{
public:
    float zoom = 125;
    bool useTwoColors = true;
    int penWidth = 1;
    QColor firstColor = Qt::blue;
    QColor secondColor = Qt::red;
    QColor backgroundColor = Qt::white;

    ImagePainter();
    ImagePainter(ImagePainter* imagePainter);
    QImage getImage(Harmonograph* harmonograph);
    QImage getImageToSave(Harmonograph* harmonograph, int width, int height);
private:
    int const drawImgWidth = 1280;
    int const drawImgHeight = 720;

    QImage* image;
    QPainter* painter;
    QPen pen;
};

