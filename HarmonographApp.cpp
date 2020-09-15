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
    
    QElapsedTimer timer;
    timer.start();
    manager->updateRandomValues();
    redrawImage();

    ui.label->setText(QString::number(timer.elapsed()));
}

void HarmonographApp::redrawImage() {
    scene->clear();
    QGraphicsPixmapItem* item = manager->getRenderedGraphicsItem();
    //item->pixmap().scaled();
    scene->addItem(item);
}

void HarmonographApp::autoRotate()
{
    //if (autoRotationTimer->isActive()) {
    //    autoRotationTimer->stop();
    //}
    //else {
    //    autoRotationTimer->start();
    //}
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("json (*.json);;All Files (*)"));
    if (!fileName.isEmpty()) {
        manager->loadParametersFromFile(fileName);
        redrawImage();
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
        tr("png image (*.json);;All Files (*)"));
    //if(!fileName.isEmpty()) manager->saveCurrentImage(fileName);
    if (!fileName.isEmpty()) manager->saveParametersToFile(fileName);



}

void HarmonographApp::zoomInOut() {

}
