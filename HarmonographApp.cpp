#include "HarmonographApp.h"

HarmonographApp::HarmonographApp(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    manager = new HarmonographManager();
    scene = new QGraphicsScene(this);
    autoRotationTimer = new QTimer(this);

    connect(autoRotationTimer, SIGNAL(timeout()), this, SLOT(autoRotationTimerTimeout()));

    ui.graphicsView->setScene(scene);
    autoRotationTimer->setInterval(17);
    
    ratioCheckBox = new QCheckBox("Ratio", this);
    ui.mainToolBar->addWidget(ratioCheckBox);

    numeratorCombo = new QComboBox(this);
    for (int i = 0; i < 6; i++) numeratorCombo->addItem(QString::number(i));
    numeratorCombo->setEnabled(false);
    ui.mainToolBar->addWidget(numeratorCombo);

    colon = new QLabel(this);
    colon->setText(" : ");
    colon->setEnabled(false);
    ui.mainToolBar->addWidget(colon);

    denominatorCombo = new QComboBox(this);
    for (int i = 0; i < 6; i++) denominatorCombo->addItem(QString::number(i));
    denominatorCombo->setEnabled(false);
    ui.mainToolBar->addWidget(denominatorCombo);

    ui.mainToolBar->addSeparator();

    circleCheckBox = new QCheckBox("Circle mode", this);
    ui.mainToolBar->addWidget(circleCheckBox);

    connect(ratioCheckBox, SIGNAL(clicked(bool)), this, SLOT(ratioCheckBoxCliked(bool)));

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

void HarmonographApp::ratioCheckBoxCliked(bool checked) {
    numeratorCombo->setEnabled(checked);
    colon->setEnabled(checked);
    denominatorCombo->setEnabled(checked);
}
