#include "ImagePainter.h"

ImagePainter::ImagePainter() {
    image = new QImage(drawImgWidth, drawImgHeight, QImage::Format_RGB888);
    image->fill(Qt::white);
    painter = new QPainter(image);
    painter->setPen(pen);
    pen.setColor(Qt::black);
    pen.setWidth(1);
}

QImage ImagePainter::getImage(Harmonograph* harmonograph) {
    painter->fillRect(0, 0, drawImgWidth, drawImgHeight, Qt::white);

    float widthAdd = drawImgWidth / 2;
    float heightAdd = drawImgHeight / 2;

    float xLast = (harmonograph->getX(0) * zoom) + widthAdd;
    float yLast = (harmonograph->getY(0) * zoom) + heightAdd;

    float xCurrent = 0;
    float yCurrent = 0;
    QColor colorA = Qt::blue;
    QColor colorB = Qt::red;


    int stepCount = (int)(255 / 1e-02) + 10;
    float stepR = ((float)(colorB.red() - colorA.red()) / stepCount);
    float stepG = ((float)(colorB.green() - colorA.green()) / stepCount);
    float stepB = ((float)(colorB.blue() - colorA.blue()) / stepCount);
    int i = 1;

    for (float t = 1e-02; t < 255; t += 1e-02) {

        pen.setColor(QColor(colorA.red() + stepR * i, colorA.green() + stepG * i, colorA.blue() + stepB * i, 255));
        painter->setPen(pen);
        xCurrent = (harmonograph->getX(t) * zoom) + widthAdd;
        yCurrent = (harmonograph->getY(t) * zoom) + heightAdd;

        painter->drawLine(xLast, yLast, xCurrent, yCurrent);

        xLast = xCurrent;
        yLast = yCurrent;
        i++;

    }
    return *image;
}
QImage ImagePainter::getImageToSave(Harmonograph* harmonograph, int width, int height) {

    std::unique_ptr<QImage> imageToSave(new QImage(width, height, QImage::Format_RGB32));
    QPainter* savePainter = new QPainter(imageToSave.get());
    QPen savePen;
    savePainter->setPen(savePen);
    //savePainter->setRenderHint(QPainter::Antialiasing, true);
    savePen.setColor(Qt::black);
    savePen.setWidth(1);

    savePainter->fillRect(0, 0, width, height, Qt::white);

    float widthAdd = width / 2;
    float heightAdd = height / 2;
    int saveZoom = (int)(zoom / ((drawImgWidth * 1.0) / width));

    float xLast = (harmonograph->getX(0) * saveZoom) + widthAdd;
    float yLast = (harmonograph->getY(0) * saveZoom) + heightAdd;

    float xCurrent = 0;
    float yCurrent = 0;
    QColor colorA = Qt::blue;
    QColor colorB = Qt::red;

    int stepCount = (int)(255 / 1e-04) + 10;
    float stepR = ((float)(colorB.red() - colorA.red()) / stepCount);
    float stepG = ((float)(colorB.green() - colorA.green()) / stepCount);
    float stepB = ((float)(colorB.blue() - colorA.blue()) / stepCount);
    int i = 1;

    for (float t = 1e-04; t < 255; t += 1e-04) {

        savePen.setColor(QColor(colorA.red() + stepR * i, colorA.green() + stepG * i, colorA.blue() + stepB * i, 255));
        savePainter->setPen(savePen);
        xCurrent = (harmonograph->getX(t) * saveZoom) + widthAdd;
        yCurrent = (harmonograph->getY(t) * saveZoom) + heightAdd;

        savePainter->drawLine(xLast, yLast, xCurrent, yCurrent);

        xLast = xCurrent;
        yLast = yCurrent;
        i++;

    }
    delete savePainter;

    return *imageToSave;
}