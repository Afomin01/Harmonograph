#include "FlexPainter.h"

FlexPainter::FlexPainter(FlexSettings* settings) {
	this->harmonograph = settings->flexGraph;
	this->backgroundColor = settings->backgroundColor;
	this->useTwoColors = settings->useTwoColors;
	this->firstColor = settings->firstColor;
	this->secondColor = settings->secondColor;
    this->penWidth = settings->penWidth;
    this->useAntialiasing = settings->useAntialiasing;
}

QImage FlexPainter::getImage(int width, int height, int zoom) {
    QPen pen;
    const std::unique_ptr<QImage> imagePtr(new QImage(width, height, QImage::Format_RGB888));
    imagePtr->fill(backgroundColor);
    QPainter painter(imagePtr.get());
    if (useAntialiasing) {
        painter.setRenderHint(QPainter::Antialiasing);
    }

    painter.setPen(pen);
    pen.setColor(Qt::black);
    pen.setWidth(penWidth);

    const float widthAdd = width / 2;
    const float heightAdd = height / 2;

    float xLast = (harmonograph->getCoordinateByTime(Dimension::x, 0) * zoom) + widthAdd;
    float yLast = (harmonograph->getCoordinateByTime(Dimension::y, 0) * zoom) + heightAdd;

    float xCurrent = 0;
    float yCurrent = 0;

    const int stepCount = static_cast<int>(255 / 1e-02) + 10;
    const float stepR = (static_cast<float>(secondColor.red() - firstColor.red()) / stepCount);
    const float stepG = (static_cast<float>(secondColor.green() - firstColor.green()) / stepCount);
    const float stepB = (static_cast<float>(secondColor.blue() - firstColor.blue()) / stepCount);
    int i = 1;

    for (float t = 1e-02; t < 255; t += 1e-02) {

        pen.setColor(QColor(firstColor.red() + stepR * i, firstColor.green() + stepG * i, firstColor.blue() + stepB * i, 255));
        painter.setPen(pen);
        xCurrent = (harmonograph->getCoordinateByTime(Dimension::x, t) * zoom) + widthAdd;
        yCurrent = (harmonograph->getCoordinateByTime(Dimension::x, t) * zoom) + heightAdd;

        painter.drawLine(xLast, yLast, xCurrent, yCurrent);

        xLast = xCurrent;
        yLast = yCurrent;
        i++;

    }
	return *imagePtr;
}
