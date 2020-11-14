#include "HarmonographApp.h"

HarmonographApp::HarmonographApp(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication::setWindowIcon(QIcon("icon256.ico"));

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
    freqPtSpinBox->setMinimum(0.5);
    freqPtSpinBox->setMaximum(50);
    freqPtSpinBox->setSingleStep(0.01);
    freqPtSpinBox->setValue(2);
    ui.mainToolBar->addWidget(freqPtSpinBox);
    
    ui.mainToolBar->addSeparator();

    QLabel* numOfPendulumsLabel = new QLabel(this);
    numOfPendulumsLabel->setText("Pendulums count: ");
    ui.mainToolBar->addWidget(numOfPendulumsLabel);

    numOfPendulumsSpinBox = new QSpinBox(this);
    numOfPendulumsSpinBox->setMinimum(1);
    numOfPendulumsSpinBox->setMaximum(4);
    numOfPendulumsSpinBox->setSingleStep(1);
    numOfPendulumsSpinBox->setValue(3);
    ui.mainToolBar->addWidget(numOfPendulumsSpinBox);

    ui.mainToolBar->addSeparator();

    QLabel* penWidthLabel = new QLabel(this);
    penWidthLabel->setText("Pen width: ");
    ui.mainToolBar->addWidget(penWidthLabel);

    penWidthSpinBox = new QSpinBox(this);
    penWidthSpinBox->setMinimum(1);
    penWidthSpinBox->setMaximum(5);
    penWidthSpinBox->setValue(1);
    ui.mainToolBar->addWidget(penWidthSpinBox);

    connect(autoRotationTimer, SIGNAL(timeout()), this, SLOT(autoRotationTimerTimeout()));

    connect(ratioCheckBox, SIGNAL(clicked(bool)), this, SLOT(ratioCheckBoxCliked(bool)));
    connect(circleCheckBox, SIGNAL(clicked(bool)), this, SLOT(circleCheckBoxClicked(bool)));

    connect(firstRatioValueCombo, SIGNAL(currentTextChanged(const QString&)), this, SLOT(firstRatioPicked(const QString&)));
    connect(secondRatioValueCombo, SIGNAL(currentTextChanged(const QString&)), this, SLOT(secondRatioPicked(const QString&)));

    connect(freqPtSpinBox, SIGNAL(valueChanged(double)), this, SLOT(freqPointChanged(double)));
    connect(numOfPendulumsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(numOfPendulumsChanged(int)));
    connect(penWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(penWidthChanged(int)));

    connect(customView, SIGNAL(zoomChanged(int)), this, SLOT(viewZoomChanged(int)));
    connect(customView, SIGNAL(rotateScene(float, float)), this, SLOT(rotateSceneXY(float, float)));

    redrawImage();

}

void HarmonographApp::updateImage(){
    
    manager->updateRandomValues();
    redrawImage();
    ui.actionUndoUpdate->setEnabled(true);
}

HarmonographApp::~HarmonographApp() {
    QThreadPool::globalInstance()->clear();
}

void HarmonographApp::redrawImage() {
    scene->clear();

    QGraphicsPixmapItem* item = manager->getRenderedGraphicsItem();
    scene->addItem(item);


    std::vector<Pendulum*> pendlums = manager->getPendlumsCopy();
    float pi = manager->pi;

    ui.firstXDamping->blockSignals(true);
    ui.firstXFreq->blockSignals(true);
    ui.firstXPhase->blockSignals(true);

    ui.firstYDamping->blockSignals(true);
    ui.firstYFreq->blockSignals(true);
    ui.firstYPhase->blockSignals(true);


    ui.firstXDamping->setValue((pendlums.at(0)->xDumping * manager->sliderMaxValue) / manager->maxDampingValue);
    ui.firstXFreq->setValue((pendlums.at(0)->xFrequencyNoise * manager->sliderMaxValue) / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
    ui.firstXPhase->setValue(((pendlums.at(0)->xPhase - (floor(pendlums.at(0)->xPhase / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi)) * (manager->sliderMaxValue + manager->sliderMaxValue / 10));

    ui.firstYDamping->setValue((pendlums.at(0)->yDumping * manager->sliderMaxValue) / manager->maxDampingValue);
    ui.firstYFreq->setValue((pendlums.at(0)->yFrequencyNoise * manager->sliderMaxValue) / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
    ui.firstYPhase->setValue(((pendlums.at(0)->yPhase - (floor(pendlums.at(0)->yPhase / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi)) * (manager->sliderMaxValue + manager->sliderMaxValue / 10));


    ui.firstXDamping->blockSignals(false);
    ui.firstXFreq->blockSignals(false);
    ui.firstXPhase->blockSignals(false);

    ui.firstYDamping->blockSignals(false);
    ui.firstYFreq->blockSignals(false);
    ui.firstYPhase->blockSignals(false);

    if (pendlums.size() >= 2) {
        ui.secondXDamping->blockSignals(true);
        ui.secondXFrequency->blockSignals(true);
        ui.secondXPhase->blockSignals(true);

        ui.secondYDamping->blockSignals(true);
        ui.secondyFrequency->blockSignals(true);
        ui.secondYPhase->blockSignals(true);


        ui.secondXDamping->setValue((pendlums.at(1)->xDumping * manager->sliderMaxValue) / manager->maxDampingValue);
        ui.secondXFrequency->setValue((pendlums.at(1)->xFrequencyNoise * manager->sliderMaxValue) / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
        ui.secondXPhase->setValue(((pendlums.at(1)->xPhase - (floor(pendlums.at(1)->xPhase / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi)) * (manager->sliderMaxValue + manager->sliderMaxValue / 10));

        ui.secondYDamping->setValue((pendlums.at(1)->yDumping * manager->sliderMaxValue) / manager->maxDampingValue);
        ui.secondyFrequency->setValue((pendlums.at(1)->yFrequencyNoise * manager->sliderMaxValue) / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
        ui.secondYPhase->setValue(((pendlums.at(1)->yPhase - (floor(pendlums.at(1)->yPhase / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi)) * (manager->sliderMaxValue + manager->sliderMaxValue / 10));


        ui.secondXDamping->blockSignals(false);
        ui.secondXFrequency->blockSignals(false);
        ui.secondXPhase->blockSignals(false);

        ui.secondYDamping->blockSignals(false);
        ui.secondyFrequency->blockSignals(false);
        ui.secondYPhase->blockSignals(false);
    }
    if (pendlums.size() >= 3) {
        ui.thridXDamping->blockSignals(true);
        ui.thirdXFrequency->blockSignals(true);
        ui.thirdXPhase->blockSignals(true);

        ui.thirdYDamping->blockSignals(true);
        ui.thirdYFrequency->blockSignals(true);
        ui.thirdYPhase->blockSignals(true);


        ui.thridXDamping->setValue((pendlums.at(2)->xDumping * manager->sliderMaxValue) / manager->maxDampingValue);
        ui.thirdXFrequency->setValue((pendlums.at(2)->xFrequencyNoise * manager->sliderMaxValue) / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
        ui.thirdXPhase->setValue(((pendlums.at(2)->xPhase - (floor(pendlums.at(2)->xPhase / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi)) * (manager->sliderMaxValue + manager->sliderMaxValue / 10));

        ui.thirdYDamping->setValue((pendlums.at(2)->yDumping * manager->sliderMaxValue) / manager->maxDampingValue);
        ui.thirdYFrequency->setValue((pendlums.at(2)->yFrequencyNoise * manager->sliderMaxValue) / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
        ui.thirdYPhase->setValue(((pendlums.at(2)->yPhase - (floor(pendlums.at(2)->yPhase / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi)) * (manager->sliderMaxValue + manager->sliderMaxValue / 10));


        ui.thridXDamping->blockSignals(false);
        ui.thirdXFrequency->blockSignals(false);
        ui.thirdXPhase->blockSignals(false);

        ui.thirdYDamping->blockSignals(false);
        ui.thirdYFrequency->blockSignals(false);
        ui.thirdYPhase->blockSignals(false);
    }
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

void HarmonographApp::undoUpdate() {
    manager->undoUpdate();
    redrawImage();
    if (manager->getHistorySize() > 0) ui.actionUndoUpdate->setEnabled(true);
    else ui.actionUndoUpdate->setEnabled(false);
}

void HarmonographApp::startFlex() {

    FlexDialog flexDialog = new FlexDialog(this);

    int code = flexDialog.exec();

    if (code==1) {
        FlexWindow* flexWindow = new FlexWindow(this, manager->getHarmCopy(), flexDialog.flexBaseCode, flexDialog.useAntiAliasing, flexDialog.penWidth, flexDialog.FPS);
        flexWindow->setFixedWidth(1280);
        flexWindow->setFixedHeight(720);
        flexWindow->show();
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
        freqPtSpinBox->blockSignals(true);
        firstRatioValueCombo->blockSignals(true);
        secondRatioValueCombo->blockSignals(true);

        autoRotationTimer->stop();
        manager->loadParametersFromFile(fileName);

        Harmonograph* harmCopy = manager->getHarmCopy();

        freqPtSpinBox->setValue(harmCopy->frequencyPoint);
        ratioCheckBox->setChecked(harmCopy->isStar);

        firstRatioValueCombo->setEnabled(harmCopy->isStar);
        colonLabel->setEnabled(harmCopy->isStar);
        secondRatioValueCombo->setEnabled(harmCopy->isStar);

        firstRatioValueCombo->setCurrentText(QString::number(harmCopy->firstRatioValue));
        secondRatioValueCombo->setCurrentText(QString::number(harmCopy->secondRatioValue));
        circleCheckBox->setChecked(harmCopy->isCircle);

        delete harmCopy;

        redrawImage();
        freqPtSpinBox->blockSignals(false);
        firstRatioValueCombo->blockSignals(false);
        secondRatioValueCombo->blockSignals(false);
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

void HarmonographApp::penWidthChanged(int width) {
    manager->changePenWidth(width);
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
    redrawImage();
}

void HarmonographApp::numOfPendulumsChanged(int newNum) {
    manager->setNumOfPendulums(newNum);

    if (newNum < 3) {
        ui.secondXDamping->setValue(0);
        ui.secondXFrequency->setValue(0);
        ui.secondXPhase->setValue(0);

        ui.secondYDamping->setValue(0);
        ui.secondyFrequency->setValue(0);
        ui.secondYPhase->setValue(0);
    }

    if (newNum < 2) {
        ui.thridXDamping->setValue(0);
        ui.thirdXFrequency->setValue(0);
        ui.thirdXPhase->setValue(0);

        ui.thirdYDamping->setValue(0);
        ui.thirdYFrequency->setValue(0);
        ui.thirdYPhase->setValue(0);
    }
    redrawImage();
}

void HarmonographApp::firstXDampingChanged(int value) {
    changeParameter(0, HarmonographParameters::xDamping, value);
}

void HarmonographApp::firstXPhaseChanged(int value) {
    changeParameter(0, HarmonographParameters::xPhase, value);
}

void HarmonographApp::firstXFrequencyChanged(int value) {
    changeParameter(0, HarmonographParameters::xFrequency, value);
}

void HarmonographApp::firstYDampingChanged(int value) {
    changeParameter(0, HarmonographParameters::yDamping, value);
}

void HarmonographApp::firstYPhaseChanged(int value) {
    changeParameter(0, HarmonographParameters::yPhase, value);
}

void HarmonographApp::firstYFrequencyChanged(int value) {
    changeParameter(0, HarmonographParameters::yFrequency, value);
}

void HarmonographApp::secondXDampingChanged(int value) {
    if(numOfPendulumsSpinBox->value()>=2) changeParameter(1, HarmonographParameters::xDamping, value);
}

void HarmonographApp::secondXPhaseChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 2) changeParameter(1, HarmonographParameters::xPhase, value);
}

void HarmonographApp::secondXFrequencyChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 2) changeParameter(1, HarmonographParameters::xFrequency, value);
}

void HarmonographApp::secondYDampingChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 2) changeParameter(1, HarmonographParameters::yDamping, value);
}

void HarmonographApp::secondYPhaseChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 2) changeParameter(1, HarmonographParameters::yPhase, value);
}

void HarmonographApp::secondYFrequencyChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 2) changeParameter(1, HarmonographParameters::yFrequency, value);
}

void HarmonographApp::thirdXDampingChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, HarmonographParameters::xDamping, value);
}

void HarmonographApp::thirdXPhaseChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, HarmonographParameters::xPhase, value);
}

void HarmonographApp::thirdXFrequencyChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, HarmonographParameters::xFrequency, value);
}

void HarmonographApp::thirdYDampingChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, HarmonographParameters::yDamping, value);
}

void HarmonographApp::thirdYPhaseChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, HarmonographParameters::yPhase, value);
}

void HarmonographApp::thirdYFrequencyChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, HarmonographParameters::yFrequency, value);
}

void HarmonographApp::viewZoomChanged(int value) {
    manager->changeZoom(value/2.0);
    redrawImage();
}

void HarmonographApp::rotateSceneXY(float x, float y) {
    manager->rotateXY(x, y);
    redrawImage();
}
