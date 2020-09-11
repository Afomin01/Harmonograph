#include "HarmonographApp.h"
#include <QElapsedTimer>
#include "Harmonograph.h"

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

void HarmonographApp::updateImage() {
    
    QElapsedTimer timer;
    timer.start();

    drawImage();

    ui.label->setText(QString::number(timer.elapsed()));
}
