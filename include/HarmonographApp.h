#pragma once

#include <QTimer>
#include <QtWidgets>
#include <QtWidgets/QMainWindow>
#include "Harmonograph.h"
#include <QGraphicsPixmapItem>
#include <ui_HarmonographApp.h>
#include <cstdlib>
#include "HarmonographManager.h"
#include <ui_HarmonographApp.h>
#include "Dimension.h"
#include "PendulumEquationParametersEnum.h"
#include "FlexWindow.h"
#include "FlexDialog.h"
#include "SaveImageDialog.h"
#include "settings.h"

class HarmonographApp : public QMainWindow {
    Q_OBJECT

public:
    HarmonographApp(QWidget* parent = Q_NULLPTR);
    ~HarmonographApp();

private:
    HarmonographManager* manager;
	
    Ui::HarmonographAppClass ui;
    HarmonographOpenGLWidget* GLWidget2D;
    QTimer* autoRotationTimer;

    QComboBox* drawModesCombo;
    QLabel* penWidthLabel, *drawModeLabel, *timeStepLabel;

    QDoubleSpinBox* timeSpinBox;
    QSpinBox* penWidthSpinBox;

    FlexDialog* flexDialog = new FlexDialog(this);
    SaveImageDialog* saveImageDialog = new SaveImageDialog(this);

    void redrawImage();
    void changeParameter(int pendulumNum, EquationParameter parameter, Dimension dimension, int value);

private slots:
    void updateImage();
    void autoRotate();
    void undoUpdate();
    void startFlex();
    void autoRotationTimerTimeout();
    void saveImage();
    void saveParametersToFile();
    void loadParametersFromFile();
    void ratioCheckBoxCliked(bool checked);
    void circleCheckBoxClicked(bool checked);
    void useTwoColorsCheckBoxChanged(bool checked);
    void penWidthChanged(int width);
    void firstRatioPicked(int ratio);
    void secondRatioPicked(int ratio);
    void freqPointChanged(double freqPoint);
    void timeStepChanged(double step);
    void numOfPendulumsChanged(int newNum);

    void primaryColorBtnClicked();
    void secondColorBtnClicked();
    void backgroundColorBtnClicked();


    void firstXDampingChanged(int value);
    void firstXPhaseChanged(int value);
    void firstXFrequencyChanged(int value);
    void firstYDampingChanged(int value);
    void firstYPhaseChanged(int value);
    void firstYFrequencyChanged(int value);

    void secondXDampingChanged(int value);
    void secondXPhaseChanged(int value);
    void secondXFrequencyChanged(int value);
    void secondYDampingChanged(int value);
    void secondYPhaseChanged(int value);
    void secondYFrequencyChanged(int value);

    void thirdXDampingChanged(int value);
    void thirdXPhaseChanged(int value);
    void thirdXFrequencyChanged(int value);
    void thirdYDampingChanged(int value);
    void thirdYPhaseChanged(int value);
    void thirdYFrequencyChanged(int value);

    void drawModeChanged(int index);
};