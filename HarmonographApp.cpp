#include "HarmonographApp.h"

HarmonographApp::HarmonographApp(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    manager = new HarmonographManager();
    scene = new QGraphicsScene(this);
    autoRotationTimer = new QTimer(this);

    connect(autoRotationTimer, SIGNAL(timeout()), this, SLOT(autoRotationTimerTimeout()));

    ui.graphicsView->setScene(scene);
    autoRotationTimer->setInterval(17);
    
    redrawImage();
}

void HarmonographApp::updateImage(){
    
    manager->updateRandomValues();
    redrawImage();
}

void HarmonographApp::redrawImage() {
    scene->clear();
    QGraphicsPixmapItem* item = manager->getRenderedGraphicsItem();
    //item->pixmap().scaled();
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
    manager->changeXAxisRotation(0.05);
    redrawImage();
}

void HarmonographApp::saveImage() {
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Harmonograph Image"), "",
        tr("png image (*.png);;All Files (*)"));
    if(!fileName.isEmpty()) manager->saveCurrentImage(fileName);
}

void HarmonographApp::zoomInOut() {

}

void HarmonographApp::saveParametersToFile() {
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Harmonograph Image"), "",
        tr("JSON (*.json);;All Files (*)"));
    if (!fileName.isEmpty()) manager->saveParametersToFile(fileName);
}

void HarmonographApp::loadParametersFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("JSON (*.json);;All Files (*)"));
    if (!fileName.isEmpty()) {
        manager->loadParametersFromFile(fileName);
        redrawImage();
    }
}
