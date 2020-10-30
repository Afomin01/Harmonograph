#include "HarmonographApp.h"


HarmonographApp::HarmonographApp(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication::setWindowIcon(QIcon("icon1.ico"));

    manager = new HarmonographManager();
    scene = new QGraphicsScene(this);
    customView = new CustomGraphicsView(this);

    auto gridLayout = dynamic_cast<QGridLayout*>(ui.centralWidget->layout());

    customView->setMinimumHeight(720);
    customView->setMinimumWidth(1280);

    customView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    customView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    gridLayout->addWidget(customView, 1, 1);

    autoRotationTimer = new QTimer(this);

    customView->setScene(scene);
    autoRotationTimer->setInterval(17);
    
    ratioCheckBox = new QCheckBox("Ratio", this);
    ui.mainToolBar->addWidget(ratioCheckBox);

    firstRatioValueCombo = new QComboBox(this);
    for (int i = 1; i < 6; i++) firstRatioValueCombo->addItem(QString::number(i));
    firstRatioValueCombo->setEnabled(false);
    firstRatioValueCombo->setCurrentIndex(0);
    ui.mainToolBar->addWidget(firstRatioValueCombo);

    colonLabel = new QLabel(this);
    colonLabel->setText(" : ");
    colonLabel->setEnabled(false);
    ui.mainToolBar->addWidget(colonLabel);

    secondRatioValueCombo = new QComboBox(this);
    for (int i = 1; i < 6; i++) secondRatioValueCombo->addItem(QString::number(i));
    secondRatioValueCombo->setEnabled(false);
    secondRatioValueCombo->setCurrentIndex(0);
    ui.mainToolBar->addWidget(secondRatioValueCombo);

    ui.mainToolBar->addSeparator();

    circleCheckBox = new QCheckBox("Circle mode", this);
    ui.mainToolBar->addWidget(circleCheckBox);

    ui.mainToolBar->addSeparator();

    QLabel* freqPointLabel = new QLabel(this);
    freqPointLabel->setText("Freq point: ");
    ui.mainToolBar->addWidget(freqPointLabel);

    freqPtSpinBox = new QDoubleSpinBox(this);
    freqPtSpinBox->setMinimum(2);
    freqPtSpinBox->setMaximum(20);
    freqPtSpinBox->setSingleStep(0.01);
    ui.mainToolBar->addWidget(freqPtSpinBox);
    
    ui.mainToolBar->addSeparator();

    QLabel* numOfPendulumsLabel = new QLabel(this);
    numOfPendulumsLabel->setText("Number of pendulums: ");
    ui.mainToolBar->addWidget(numOfPendulumsLabel);

    numOfPendulumsSpinBox = new QSpinBox(this);
    numOfPendulumsSpinBox->setMinimum(1);
    numOfPendulumsSpinBox->setMaximum(3);
    numOfPendulumsSpinBox->setSingleStep(1);
    numOfPendulumsSpinBox->setValue(3);
    ui.mainToolBar->addWidget(numOfPendulumsSpinBox);


    connect(autoRotationTimer, SIGNAL(timeout()), this, SLOT(autoRotationTimerTimeout()));

    connect(ratioCheckBox, SIGNAL(clicked(bool)), this, SLOT(ratioCheckBoxCliked(bool)));
    connect(circleCheckBox, SIGNAL(clicked(bool)), this, SLOT(circleCheckBoxClicked(bool)));

    connect(firstRatioValueCombo, SIGNAL(currentTextChanged(const QString&)), this, SLOT(firstRatioPicked(const QString&)));
    connect(secondRatioValueCombo, SIGNAL(currentTextChanged(const QString&)), this, SLOT(secondRatioPicked(const QString&)));

    connect(freqPtSpinBox, SIGNAL(valueChanged(double)), this, SLOT(freqPointChanged(double)));
    connect(numOfPendulumsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(numOfPendulumsChanged(int)));

    connect(customView, SIGNAL(zoomChanged(int)), this, SLOT(viewZoomChanged(int)));
    connect(customView, SIGNAL(rotateScene(float, float)), this, SLOT(rotateSceneXY(float, float)));

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

void HarmonographApp::changeParameter(int pendulumNum, HarmonographParameters parameter, int value) {
    manager->changeParameter(pendulumNum, parameter, value);
    redrawImage();
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
    if (autoRotationTimer->isActive()) {
        autoRotationTimer->stop();

        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Harmonograph Image"), "",
            tr("png image (*.png);;All Files (*)"));
        if (!fileName.isEmpty()) manager->saveCurrentImage(fileName);

        autoRotationTimer->start();
    }
    else {
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Harmonograph Image"), "",
            tr("png image (*.png);;All Files (*)"));
        if (!fileName.isEmpty()) manager->saveCurrentImage(fileName);
    }
}

void HarmonographApp::saveParametersToFile() {
    if (autoRotationTimer->isActive()) {
        autoRotationTimer->stop();

        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Harmonogrph parameters"), "",
            tr("JSON (*.json);;All Files (*)"));
        if (!fileName.isEmpty()) manager->saveParametersToFile(fileName);

        autoRotationTimer->start();
    }
    else {
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Harmonogrph parameters"), "",
            tr("JSON (*.json);;All Files (*)"));
        if (!fileName.isEmpty()) manager->saveParametersToFile(fileName);
    }
}

void HarmonographApp::loadParametersFromFile() {

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Harmonogrph parameters"), "",
        tr("JSON (*.json);;All Files (*)"));
    if (!fileName.isEmpty()) {
        autoRotationTimer->stop();
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

void HarmonographApp::freqPointChanged(double freqPoint) {
    manager->setFrequencyPoint(freqPoint);
    manager->updateRandomValues();
    redrawImage();
}

void HarmonographApp::numOfPendulumsChanged(int newNum) {
    manager->setNumOfPendulums(newNum);
    redrawImage();
}

void HarmonographApp::firstXDampingChanged(int value) {
    changeParameter(1, HarmonographParameters::xDamping, value);
}

void HarmonographApp::firstXPhaseChanged(int value) {
    changeParameter(1, HarmonographParameters::xPhase, value);
}

void HarmonographApp::firstXFrequencyChanged(int value) {
    changeParameter(1, HarmonographParameters::xFrequency, value);
}

void HarmonographApp::firstYDampingChanged(int value) {
    changeParameter(1, HarmonographParameters::yDamping, value);
}

void HarmonographApp::firstYPhaseChanged(int value) {
    changeParameter(1, HarmonographParameters::yPhase, value);
}

void HarmonographApp::firstYFrequencyChanged(int value) {
    changeParameter(1, HarmonographParameters::yFrequency, value);
}

void HarmonographApp::viewZoomChanged(int value) {
    manager->changeZoom(value/2.0);
    redrawImage();
}

void HarmonographApp::rotateSceneXY(float x, float y) {
    manager->rotateXY(x, y);
    redrawImage();
}
