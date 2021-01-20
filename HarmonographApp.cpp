#include "HarmonographApp.h"

HarmonographApp::HarmonographApp(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication::setWindowIcon(QIcon("icon256.ico"));

    manager = new HarmonographManager();

    autoRotationTimer = new QTimer(this);
    autoRotationTimer->setInterval(17);

    auto gridLayout2D = dynamic_cast<QGridLayout*>(ui.tab2D->layout());
    GLWidget2D = new HarmonographOpenGLWidget(this, manager);
    GLWidget2D->setMinimumHeight(720);
    GLWidget2D->setMinimumWidth(1280);
    GLWidget2D->setEnableAA(true);
    gridLayout2D->addWidget(GLWidget2D, 1, 1);

    auto gridLayout3D = dynamic_cast<QGridLayout*>(ui.tab3D->layout());

    //gridLayout3D->addWidget(openGLWidget, 1, 1);
    
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

    freqPointLabel = new QLabel(this);
    freqPointLabel->setText("Freq point: ");
    ui.mainToolBar->addWidget(freqPointLabel);

    freqPtSpinBox = new QDoubleSpinBox(this);
    freqPtSpinBox->setMinimum(0.5);
    freqPtSpinBox->setMaximum(50);
    freqPtSpinBox->setSingleStep(0.01);
    freqPtSpinBox->setValue(2);
    ui.mainToolBar->addWidget(freqPtSpinBox);
    
    ui.mainToolBar->addSeparator();

    numOfPendulumsLabel = new QLabel(this);
    numOfPendulumsLabel->setText("Pendulums count: ");
    ui.mainToolBar->addWidget(numOfPendulumsLabel);

    numOfPendulumsSpinBox = new QSpinBox(this);
    numOfPendulumsSpinBox->setMinimum(1);
    numOfPendulumsSpinBox->setMaximum(4);
    numOfPendulumsSpinBox->setSingleStep(1);
    numOfPendulumsSpinBox->setValue(3);
    ui.mainToolBar->addWidget(numOfPendulumsSpinBox);

    ui.mainToolBar->addSeparator();

    penWidthLabel = new QLabel(this);
    penWidthLabel->setText("Pen width: ");
    ui.mainToolBar->addWidget(penWidthLabel);

    penWidthSpinBox = new QSpinBox(this);
    penWidthSpinBox->setMinimum(1);
    penWidthSpinBox->setMaximum(5);
    penWidthSpinBox->setValue(1);
    ui.mainToolBar->addWidget(penWidthSpinBox);

    ui.mainToolBar->addSeparator();

    drawModeLabel = new QLabel(this);
    drawModeLabel->setText("Mode: ");
    ui.mainToolBar->addWidget(drawModeLabel);

    ui.mainToolBar->addSeparator();

    drawModesCombo = new QComboBox(this);
    drawModesCombo->addItem("lines");
    drawModesCombo->addItem("points");
    ui.mainToolBar->addWidget(drawModesCombo);

    ui.mainToolBar->addSeparator();

    timeStepLabel = new QLabel(this);
    timeStepLabel->setText("Time step: ");
    ui.mainToolBar->addWidget(timeStepLabel);

    ui.mainToolBar->addSeparator();

    timeSpinBox = new QDoubleSpinBox(this);
    timeSpinBox->setMinimum(0.01);
    timeSpinBox->setMaximum(0.1);
    timeSpinBox->setSingleStep(0.01);
    timeSpinBox->setValue(0.01);
    ui.mainToolBar->addWidget(timeSpinBox);

    ui.mainToolBar->addSeparator();

    QPushButton* primaryColorBtn = new QPushButton(this);
    primaryColorBtn->setText("Primary color");
    ui.mainToolBar->addWidget(primaryColorBtn);

    ui.mainToolBar->addSeparator();

    QPushButton* secondColorBtn = new QPushButton(this);
    secondColorBtn->setText("Second color");
    ui.mainToolBar->addWidget(secondColorBtn);

    ui.mainToolBar->addSeparator();

    QCheckBox* useTwoColorsCheckBox = new QCheckBox(this);
    useTwoColorsCheckBox->setText("Use two colors");
    useTwoColorsCheckBox->setChecked(true);
    ui.mainToolBar->addWidget(useTwoColorsCheckBox);

    ui.mainToolBar->addSeparator();

    QPushButton* backColorBtn = new QPushButton(this);
    backColorBtn->setText("Background color");
    ui.mainToolBar->addWidget(backColorBtn);

    connect(autoRotationTimer, SIGNAL(timeout()), this, SLOT(autoRotationTimerTimeout()));

    connect(ratioCheckBox, SIGNAL(clicked(bool)), this, SLOT(ratioCheckBoxCliked(bool)));
    connect(circleCheckBox, SIGNAL(clicked(bool)), this, SLOT(circleCheckBoxClicked(bool)));
    connect(useTwoColorsCheckBox, SIGNAL(clicked(bool)), this, SLOT(useTwoColorsCheckBoxChanged(bool)));

    connect(firstRatioValueCombo, SIGNAL(currentTextChanged(const QString&)), this, SLOT(firstRatioPicked(const QString&)));
    connect(secondRatioValueCombo, SIGNAL(currentTextChanged(const QString&)), this, SLOT(secondRatioPicked(const QString&)));

    connect(freqPtSpinBox, SIGNAL(valueChanged(double)), this, SLOT(freqPointChanged(double)));
    connect(timeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(timeStepChanged(double)));
    connect(numOfPendulumsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(numOfPendulumsChanged(int)));
    connect(penWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(penWidthChanged(int)));

    connect(drawModesCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(drawModeChanged(int)));

    connect(primaryColorBtn, SIGNAL(clicked()), this, SLOT(primaryColorBtnClicked()));
    connect(secondColorBtn, SIGNAL(clicked()), this, SLOT(secondColorBtnClicked()));
    connect(backColorBtn, SIGNAL(clicked()), this, SLOT(backgroundColorBtnClicked()));

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
	GLWidget2D->update();

    std::vector<Pendulum*> pendlums = manager->getPendulumsCopy();
    float pi = manager->pi;

    ui.firstXDamping->blockSignals(true);
    ui.firstXFreq->blockSignals(true);
    ui.firstXPhase->blockSignals(true);

    ui.firstYDamping->blockSignals(true);
    ui.firstYFreq->blockSignals(true);
    ui.firstYPhase->blockSignals(true);


    ui.firstXDamping->setValue((pendlums.at(0)->getEquationParameter(Dimension::x, EquationParameter::dumping) * manager->sliderMaxValue) / manager->maxDampingValue);
    ui.firstXFreq->setValue((pendlums.at(0)->getEquationParameter(Dimension::x, EquationParameter::frequencyNoise) * manager->sliderMaxValue) / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
	
    ui.firstXPhase->setValue(((pendlums.at(0)->getEquationParameter(Dimension::x, EquationParameter::phase) -
        (floor(pendlums.at(0)->getEquationParameter(Dimension::x, EquationParameter::phase) / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi))
        * (manager->sliderMaxValue + manager->sliderMaxValue / 10));

	
    ui.firstYDamping->setValue((pendlums.at(0)->getEquationParameter(Dimension::y, EquationParameter::dumping) * manager->sliderMaxValue) / manager->maxDampingValue);
    ui.firstYFreq->setValue((pendlums.at(0)->getEquationParameter(Dimension::y, EquationParameter::frequencyNoise) * manager->sliderMaxValue)
        / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
	
    ui.firstYPhase->setValue(((pendlums.at(0)->getEquationParameter(Dimension::y, EquationParameter::phase) -
        (floor(pendlums.at(0)->getEquationParameter(Dimension::y, EquationParameter::phase) / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi))
        * (manager->sliderMaxValue + manager->sliderMaxValue / 10));


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


        ui.secondXDamping->setValue((pendlums.at(1)->getEquationParameter(Dimension::x, EquationParameter::dumping) * manager->sliderMaxValue) / manager->maxDampingValue);
        ui.secondXFrequency->setValue((pendlums.at(1)->getEquationParameter(Dimension::x, EquationParameter::frequencyNoise) * manager->sliderMaxValue) / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
        ui.secondXPhase->setValue(((pendlums.at(1)->getEquationParameter(Dimension::x, EquationParameter::phase) - (floor(pendlums.at(1)->getEquationParameter(Dimension::x, EquationParameter::phase) / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi)) * (manager->sliderMaxValue + manager->sliderMaxValue / 10));

        ui.secondYDamping->setValue((pendlums.at(1)->getEquationParameter(Dimension::y, EquationParameter::dumping) * manager->sliderMaxValue) / manager->maxDampingValue);
        ui.secondyFrequency->setValue((pendlums.at(1)->getEquationParameter(Dimension::y, EquationParameter::frequencyNoise) * manager->sliderMaxValue) / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
        ui.secondYPhase->setValue(((pendlums.at(1)->getEquationParameter(Dimension::y, EquationParameter::phase) - (floor(pendlums.at(1)->getEquationParameter(Dimension::x, EquationParameter::phase) / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi)) * (manager->sliderMaxValue + manager->sliderMaxValue / 10));


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


        ui.thridXDamping->setValue((pendlums.at(2)->getEquationParameter(Dimension::x, EquationParameter::dumping) * manager->sliderMaxValue) / manager->maxDampingValue);
        ui.thirdXFrequency->setValue((pendlums.at(2)->getEquationParameter(Dimension::x, EquationParameter::frequencyNoise) * manager->sliderMaxValue) / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
        ui.thirdXPhase->setValue(((pendlums.at(2)->getEquationParameter(Dimension::x, EquationParameter::phase) - (floor(pendlums.at(2)->getEquationParameter(Dimension::x, EquationParameter::phase) / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi)) * (manager->sliderMaxValue + manager->sliderMaxValue / 10));

        ui.thirdYDamping->setValue((pendlums.at(2)->getEquationParameter(Dimension::y, EquationParameter::dumping) * manager->sliderMaxValue) / manager->maxDampingValue);
        ui.thirdYFrequency->setValue((pendlums.at(2)->getEquationParameter(Dimension::y, EquationParameter::frequencyNoise) * manager->sliderMaxValue) / (2 * manager->maxFreqModuleValue) + (manager->sliderMaxValue / 2));
        ui.thirdYPhase->setValue(((pendlums.at(2)->getEquationParameter(Dimension::y, EquationParameter::phase) - (floor(pendlums.at(2)->getEquationParameter(Dimension::y, EquationParameter::phase) / (2.0 * pi)) * 2.0 * pi)) / (2.0 * pi)) * (manager->sliderMaxValue + manager->sliderMaxValue / 10));


        ui.thridXDamping->blockSignals(false);
        ui.thirdXFrequency->blockSignals(false);
        ui.thirdXPhase->blockSignals(false);

        ui.thirdYDamping->blockSignals(false);
        ui.thirdYFrequency->blockSignals(false);
        ui.thirdYPhase->blockSignals(false);
    }
}

void HarmonographApp::changeParameter(int pendulumNum, EquationParameter parameter, Dimension dimension, int value) {
    manager->changeParameter(pendulumNum, parameter, dimension, value);
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

    int code = flexDialog->exec();

    if (code==1) {
        DrawParameters params = manager->getDrawParameters();
        FlexSettings* flexSettings = new FlexSettings();
        flexSettings->flexGraph = manager->getHarmCopy();
        flexSettings->flexBaseMode = flexDialog->flexBaseMode;
        params.useAntiAliasing = flexDialog->useAntiAliasing;
        flexSettings->FPSLimit = flexDialog->FPS;

        flexSettings->parameters = params;
        FlexWindow* flexWindow = new FlexWindow(flexSettings, this);
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
    bool wasRotationActive = autoRotationTimer->isActive();
    autoRotationTimer->stop();

    int code = saveImageDialog->exec();

    if (code == 1) {
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Harmonograph Image"), "",
            tr("png image (*.png);;All Files (*)"));
        if (!fileName.isEmpty()) {
            ImageSettings* imageSettings = new ImageSettings();
            imageSettings->parameters = manager->getDrawParameters();
        	
            imageSettings->filename = fileName;
            if (saveImageDialog->transpBack) imageSettings->parameters.backgroundColor = QColor(0, 0, 0, 0);
            imageSettings->parameters.penWidth = saveImageDialog->penWidth;
            imageSettings->parameters.useAntiAliasing = saveImageDialog->useAntialiasing;
            imageSettings->useSquareImage = saveImageDialog->useSquareImage;
            imageSettings->saveWidth = saveImageDialog->saveWidth;
            imageSettings->saveHeight = saveImageDialog->saveHeight;
            imageSettings->borderPercentage = saveImageDialog->borderPercentage;

            manager->saveCurrentImage(imageSettings);
        }
    }
    if (wasRotationActive) autoRotationTimer->start();
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

    manager->setRatioStateEnabled(checked);
    redrawImage();
}

void HarmonographApp::circleCheckBoxClicked(bool checked) {
    manager->setIsCircleEnabled(checked);
    redrawImage();
}

void HarmonographApp::useTwoColorsCheckBoxChanged(bool checked) {
    manager->setUseTwoColors(checked);
    redrawImage();
}

void HarmonographApp::penWidthChanged(int width) {
    manager->setPenWidth(width);
    redrawImage();
}

void HarmonographApp::firstRatioPicked(const QString& text) {
    manager->setFirstRatioValue(text.toInt());
    redrawImage();
}

void HarmonographApp::secondRatioPicked(const QString& text) {
    manager->setSecondRatioValue(text.toInt());
    redrawImage();
}

void HarmonographApp::freqPointChanged(double freqPoint) {
    manager->setFrequencyPoint(freqPoint);
    redrawImage();
}

void HarmonographApp::timeStepChanged(double step) {
    step = step < 0.001 ? 0.001 : step;
    step = step > 0.1 ? 0.1 : step;
    manager->setTimeStep(step);
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

void HarmonographApp::primaryColorBtnClicked() {
    QColor color = QColorDialog::getColor(manager->getDrawParameters().primaryColor, this, "Select primary color");
    if(color.isValid()) {
        manager->setPrimaryColor(color);
        redrawImage();
    }
}

void HarmonographApp::secondColorBtnClicked() {
    QColor color = QColorDialog::getColor(manager->getDrawParameters().secondColor, this, "Select second color");
    if (color.isValid()) {
        manager->setSecondColor(color);
        redrawImage();
    }	
}

void HarmonographApp::backgroundColorBtnClicked() {
    QColor color = QColorDialog::getColor(manager->getDrawParameters().backgroundColor, this, "Select background color");
    if (color.isValid()) {
        manager->setBackgroundColor(color);
        redrawImage();
        GLWidget2D->update();
    	
    }
}

void HarmonographApp::firstXDampingChanged(int value) {
    changeParameter(0, EquationParameter::dumping, Dimension::x, value);
}

void HarmonographApp::firstXPhaseChanged(int value) {
    changeParameter(0, EquationParameter::phase, Dimension::x, value);
}

void HarmonographApp::firstXFrequencyChanged(int value) {
    changeParameter(0, EquationParameter::frequency, Dimension::x, value);
}

void HarmonographApp::firstYDampingChanged(int value) {
    changeParameter(0, EquationParameter::dumping, Dimension::y, value);
}

void HarmonographApp::firstYPhaseChanged(int value) {
    changeParameter(0, EquationParameter::phase, Dimension::y, value);
}

void HarmonographApp::firstYFrequencyChanged(int value) {
    changeParameter(0, EquationParameter::frequency, Dimension::y, value);
}

void HarmonographApp::secondXDampingChanged(int value) {
    if(numOfPendulumsSpinBox->value()>=2) changeParameter(1, EquationParameter::dumping, Dimension::x, value);
}

void HarmonographApp::secondXPhaseChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 2) changeParameter(1, EquationParameter::phase, Dimension::x, value);
}

void HarmonographApp::secondXFrequencyChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 2) changeParameter(1, EquationParameter::frequency, Dimension::x, value);
}

void HarmonographApp::secondYDampingChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 2) changeParameter(1, EquationParameter::dumping, Dimension::y, value);
}

void HarmonographApp::secondYPhaseChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 2) changeParameter(1, EquationParameter::phase, Dimension::y, value);
}

void HarmonographApp::secondYFrequencyChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 2) changeParameter(1, EquationParameter::frequency, Dimension::y, value);
}

void HarmonographApp::thirdXDampingChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, EquationParameter::dumping, Dimension::x, value);
}

void HarmonographApp::thirdXPhaseChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, EquationParameter::phase, Dimension::x, value);
}

void HarmonographApp::thirdXFrequencyChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, EquationParameter::frequency, Dimension::x, value);
}

void HarmonographApp::thirdYDampingChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, EquationParameter::dumping, Dimension::y, value);
}

void HarmonographApp::thirdYPhaseChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, EquationParameter::phase, Dimension::y, value);
}

void HarmonographApp::thirdYFrequencyChanged(int value) {
    if (numOfPendulumsSpinBox->value() >= 3) changeParameter(2, EquationParameter::frequency, Dimension::y, value);
}

void HarmonographApp::drawModeChanged(int index) {
    DrawModes drawMode;
    switch (index) {
    case 0:
        drawMode = DrawModes::linesMode;
        break;
    case 1:
        drawMode = DrawModes::pointsMode;
        break;
	default:
        drawMode = DrawModes::linesMode;
    	break;
    }
    manager->setDrawMode(drawMode);
    redrawImage();
}
