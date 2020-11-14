#include "FlexPainter.h"

FlexPainter::FlexPainter(Harmonograph* harmonograph, QColor backgroundColor, bool useTwoColors, QColor firstColor, QColor secondColor, int penWidth, bool useAntialiasing) {
	this->harmonograph = harmonograph;
	this->backgroundColor = backgroundColor;
	this->useTwoColors = useTwoColors;
	this->firstColor = firstColor;
	this->secondColor = secondColor;
    this->penWidth = penWidth;
    this->useAntialiasing = useAntialiasing;
}

QImage FlexPainter::getImage(int width, int height, int zoom) {
    QPen pen;
    std::unique_ptr<QImage> imagePtr(new QImage(width, height, QImage::Format_RGB888));
    imagePtr.get()->fill(backgroundColor);
    QPainter painter(imagePtr.get());
    if (useAntialiasing) {
        painter.setRenderHint(QPainter::Antialiasing);
    }

    painter.setPen(pen);
    pen.setColor(Qt::black);
    pen.setWidth(penWidth);

    float widthAdd = width / 2;
    float heightAdd = height / 2;

    float xLast = (harmonograph->getX(0) * zoom) + widthAdd;
    float yLast = (harmonograph->getY(0) * zoom) + heightAdd;

    float xCurrent = 0;
    float yCurrent = 0;

    int stepCount = (int)(255 / 1e-02) + 10;
    float stepR = ((float)(secondColor.red() - firstColor.red()) / stepCount);
    float stepG = ((float)(secondColor.green() - firstColor.green()) / stepCount);
    float stepB = ((float)(secondColor.blue() - firstColor.blue()) / stepCount);
    int i = 1;

    for (float t = 1e-02; t < 255; t += 1e-02) {

        pen.setColor(QColor(firstColor.red() + stepR * i, firstColor.green() + stepG * i, firstColor.blue() + stepB * i, 255));
        painter.setPen(pen);
        xCurrent = (harmonograph->getX(t) * zoom) + widthAdd;
        yCurrent = (harmonograph->getY(t) * zoom) + heightAdd;

        painter.drawLine(xLast, yLast, xCurrent, yCurrent);

        xLast = xCurrent;
        yLast = yCurrent;
        i++;

    }
	return *imagePtr.get();
}
