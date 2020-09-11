#include "HarmonographApp.h"
#include "Harmonograph.h"

HarmonographApp::HarmonographApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    scene = new QGraphicsScene(this);
    ui.graphicsView->setScene(scene);

    Harmonograph* harmonograph = new Harmonograph(3);

    float zoom = 100;
    float xLast = harmonograph->getX(0)*zoom;
    float yLast = harmonograph->getY(0)*zoom;
    float xCurrent = 0;
    float yCurrent = 0;

    for (float t = 1e-01; t < 255; t += 1e-01) {

        xCurrent = harmonograph->getX(t)*zoom;
        yCurrent = harmonograph->getY(t)*zoom;

        scene->addLine(xLast, yLast, xCurrent, yCurrent, QPen(Qt::black));

        xLast = xCurrent;
        yLast = yCurrent;
    }

    delete harmonograph;

}
