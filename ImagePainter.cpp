#include "ImagePainter.h"
#include <qdebug.h>

ImagePainter::ImagePainter() {
    image = new QImage(drawImgWidth, drawImgHeight, QImage::Format_RGB888);
    image->fill(backgroundColor);
    painter = new QPainter(image);
    painter->setPen(pen);
    pen.setColor(Qt::black);
    pen.setWidth(1);
}

ImagePainter::ImagePainter(ImagePainter* imagePainter) {
    zoom = imagePainter->zoom;
    useTwoColors = imagePainter->useTwoColors;
    firstColor = imagePainter->firstColor;
    secondColor = imagePainter->secondColor;
    backgroundColor = imagePainter->backgroundColor;

    ImagePainter();
}

QImage ImagePainter::getImage(Harmonograph* harmonograph) {
    pen.setWidth(penWidth);
    painter->fillRect(0, 0, drawImgWidth, drawImgHeight, backgroundColor);
    painter->eraseRect(0, 0, drawImgWidth, drawImgHeight);

    float widthAdd = drawImgWidth / 2;
    float heightAdd = drawImgHeight / 2;

    float xLast = (harmonograph->getCoordinateByTime(Dimension::x, 0) * zoom) + widthAdd;
    float yLast = (harmonograph->getCoordinateByTime(Dimension::y, 0) * zoom) + heightAdd;

    float xCurrent = 0;
    float yCurrent = 0;


    int stepCount = (int)(255 / 1e-02) + 10;
    float stepR = ((float)(secondColor.red() - firstColor.red()) / stepCount);
    float stepG = ((float)(secondColor.green() - firstColor.green()) / stepCount);
    float stepB = ((float)(secondColor.blue() - firstColor.blue()) / stepCount);
    int i = 1;

    for (float t = 1e-02; t < 255; t += 1e-02) {

        pen.setColor(QColor(firstColor.red() + stepR * i, firstColor.green() + stepG * i, firstColor.blue() + stepB * i, 255));
        painter->setPen(pen);
        xCurrent = (harmonograph->getCoordinateByTime(Dimension::x, t) * zoom) + widthAdd;
        yCurrent = (harmonograph->getCoordinateByTime(Dimension::y, t) * zoom) + heightAdd;

        painter->drawLine(xLast, yLast, xCurrent, yCurrent);

        xLast = xCurrent;
        yLast = yCurrent;
        i++;

    }
    delete harmonograph;
    return *image;
}
QImage ImagePainter::getImageToSave(Harmonograph* harmonograph, int width, int height) {
    float const borderPercentage = 0.03;

    std::unique_ptr<QImage> imageToSave(new QImage(width, height, QImage::Format_ARGB32));
    QPainter* savePainter = new QPainter(imageToSave.get());
    QPen savePen;

    if (useAntialiasing) savePainter->setRenderHint(QPainter::Antialiasing, true);
    savePen.setColor(Qt::black);
    savePen.setWidth(penWidth);
    savePainter->setPen(savePen);

    savePainter->fillRect(0, 0, width, height, backgroundColor);

    float widthAdd = width / 2;
    float heightAdd = height / 2;

    int saveZoom = (int)(zoom / ((drawImgWidth * 1.0) / width));

    int stepCount = (int)(255 / 1e-04) + 10;
    float stepR = ((float)(secondColor.red() - firstColor.red()) / stepCount);
    float stepG = ((float)(secondColor.green() - firstColor.green()) / stepCount);
    float stepB = ((float)(secondColor.blue() - firstColor.blue()) / stepCount);

    if (saveSquare) {
        float maxX = 0, maxY = 0, maxTotal = 0;

        for (float t = 0; t < 225; t += 1e-02) {
            float x = harmonograph->getCoordinateByTime(Dimension::x, t);
            float y = harmonograph->getCoordinateByTime(Dimension::y, t);
            if (x > maxX) maxX = x;
            if (y > maxY) maxY = y;
        }

        maxTotal = maxX > maxY ? maxX : maxY;

        saveZoom = (width/2) / maxTotal;
        saveZoom -= saveZoom * borderPercentage;
    }

    int i = 1;

    float xLast = (harmonograph->getCoordinateByTime(Dimension::x, 0) * saveZoom) + widthAdd;
    float yLast = (harmonograph->getCoordinateByTime(Dimension::y, 0) * saveZoom) + heightAdd;

    float xCurrent = 0;
    float yCurrent = 0;

    for (float t = 1e-04; t < 255; t += 1e-04) {

        savePen.setColor(QColor(firstColor.red() + stepR * i, firstColor.green() + stepG * i, firstColor.blue() + stepB * i, 255));
        savePainter->setPen(savePen);
        xCurrent = (harmonograph->getCoordinateByTime(Dimension::x, t) * saveZoom) + widthAdd;
        yCurrent = (harmonograph->getCoordinateByTime(Dimension::y, t) * saveZoom) + heightAdd;

        savePainter->drawLine(xLast, yLast, xCurrent, yCurrent);

        xLast = xCurrent;
        yLast = yCurrent;
        i++;

    }
    delete savePainter;

    return *imageToSave;
}