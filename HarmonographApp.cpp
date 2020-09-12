#include "HarmonographApp.h"

HarmonographApp::HarmonographApp(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    scene = new QGraphicsScene(this);

    ui.graphicsView->setScene(scene);

    harmonograph = new Harmonograph(3);

    image = new QImage(drawImgWidth, drawImgHeight, QImage::Format_RGB888);
    image->fill(Qt::white);
    painter = new QPainter(image);
    painter->setPen(pen);
    pen.setColor(Qt::black);
    pen.setWidth(1);
    
    drawImage();
}

void HarmonographApp::drawImage() {
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

void HarmonographApp::updateImage() {
    
    QElapsedTimer timer;
    timer.start();

    drawImage();

    ui.label->setText(QString::number(timer.elapsed()));
    ui.label->setText(QString::number(rand()));
}
