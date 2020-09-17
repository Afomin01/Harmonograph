#include "HarmonographApp.h"

HarmonographApp::HarmonographApp(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    manager = new HarmonographManager();
    scene = new QGraphicsScene(this);
    autoRotationTimer = new QTimer(this);

    ui.graphicsView->setScene(scene);
    autoRotationTimer->setInterval(17);
    
    ratioCheckBox = new QCheckBox("Ratio", this);
    ui.mainToolBar->addWidget(ratioCheckBox);

    firstRatioValueCombo = new QComboBox(this);
    for (int i = 0; i < 6; i++) firstRatioValueCombo->addItem(QString::number(i));
    firstRatioValueCombo->setEnabled(false);
    ui.mainToolBar->addWidget(firstRatioValueCombo);

    colonLabel = new QLabel(this);
    colonLabel->setText(" : ");
    colonLabel->setEnabled(false);
    ui.mainToolBar->addWidget(colonLabel);

    secondRatioValueCombo = new QComboBox(this);
    for (int i = 0; i < 6; i++) secondRatioValueCombo->addItem(QString::number(i));
    secondRatioValueCombo->setEnabled(false);
    ui.mainToolBar->addWidget(secondRatioValueCombo);

    ui.mainToolBar->addSeparator();

    circleCheckBox = new QCheckBox("Circle mode", this);
    ui.mainToolBar->addWidget(circleCheckBox);

    connect(autoRotationTimer, SIGNAL(timeout()), this, SLOT(autoRotationTimerTimeout()));

    connect(ratioCheckBox, SIGNAL(clicked(bool)), this, SLOT(ratioCheckBoxCliked(bool)));
    connect(circleCheckBox, SIGNAL(clicked(bool)), this, SLOT(circleCheckBoxClicked(bool)));

    connect(firstRatioValueCombo, SIGNAL(currentTextChanged(const QString&)), this, SLOT(firstRatioPicked(const QString&)));
    connect(secondRatioValueCombo, SIGNAL(currentTextChanged(const QString&)), this, SLOT(secondRatioPicked(const QString&)));

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
        tr("Save Harmonogrph parameters"), "",
        tr("JSON (*.json);;All Files (*)"));
    if (!fileName.isEmpty()) manager->saveParametersToFile(fileName);
}

void HarmonographApp::loadParametersFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Harmonogrph parameters"), "",
        tr("JSON (*.json);;All Files (*)"));
    if (!fileName.isEmpty()) {
        manager->loadParametersFromFile(fileName);
        redrawImage();
    }
}

void HarmonographApp::ratioCheckBoxCliked(bool checked) {
    firstRatioValueCombo->setEnabled(checked);
    colonLabel->setEnabled(checked);
    secondRatioValueCombo->setEnabled(checked);

    manager->ratioStateEnabled(checked);
    redrawImage();
}

void HarmonographApp::circleCheckBoxClicked(bool checked) {
    manager->circleStateEnabled(checked);
    redrawImage();
}

void HarmonographApp::firstRatioPicked(const QString& text) {
    manager->changeFirstRatioValue(text.toInt());
    redrawImage();
}

void HarmonographApp::secondRatioPicked(const QString& text) {
    manager->changeSecondRatioValue(text.toInt());
    redrawImage();
}
