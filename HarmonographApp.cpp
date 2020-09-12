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
    autoRotationTimer = new QTimer(this);
    
    drawImage();

    autoRotationTimer->setInterval(17);
    connect(autoRotationTimer, SIGNAL(timeout()), this, SLOT(autoRotationTimerTimeout()));
}

void HarmonographApp::updateImage(){
    
    QElapsedTimer timer;
    timer.start();
    harmonograph->update();
    drawImage();

    ui.label->setText(QString::number(timer.elapsed()));
}

void HarmonographApp::drawImage(){

    painter->fillRect(0, 0, drawImgWidth, drawImgHeight, Qt::white);

    float xLast = (harmonograph->getX(0) * zoom) + (drawImgWidth / 2);
    float yLast = (harmonograph->getY(0) * zoom) + (drawImgHeight / 2);
    float xCurrent = 0;
    float yCurrent = 0;
    QColor colorA = Qt::blue;
    QColor colorB = Qt::red;


    int stepCount = (int)(255 / 1e-02);
    float stepR = ((float)(colorB.red() - colorA.red()) / (stepCount + 10));
    float stepG = ((float)(colorB.green() - colorA.green()) / (stepCount + 10));
    float stepB = ((float)(colorB.blue() - colorA.blue()) / (stepCount + 10));
    int i = 1;

    for (float t = 1e-02; t < 255; t += 1e-02) {

        pen.setColor(QColor(colorA.red() + stepR * i, colorA.green() + stepG * i, colorA.blue() + stepB * i, 255));
        painter->setPen(pen);
        xCurrent = (harmonograph->getX(t) * zoom) + (drawImgWidth / 2);
        yCurrent = (harmonograph->getY(t) * zoom) + (drawImgHeight / 2);

        painter->drawLine(xLast, yLast, xCurrent, yCurrent);

        xLast = xCurrent;
        yLast = yCurrent;
        i++;

    }

    scene->clear();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
    scene->addItem(item);
}

void HarmonographApp::autoRotate()
{
    if (autoRotationTimer->isActive()) {
        autoRotationTimer->stop();
    }
    else {
        autoRotationTimer->start();
    }
}

void HarmonographApp::autoRotationTimerTimeout()
{
    harmonograph->rotateYAxis(0.1);
    drawImage();
}
