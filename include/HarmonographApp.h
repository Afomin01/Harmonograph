#pragma once

#include <QTimer>
#include <QtWidgets>
#include <QtWidgets/QMainWindow>
#include "Harmonograph.h"
#include <QGraphicsPixmapItem>
#include <ui_HarmonographApp.h>
#include "Harmonograph.h"
#include <cstdlib>
#include "HarmonographManager.h"
#include "CustomGraphicsView.h"

class HarmonographApp : public QMainWindow
{
    Q_OBJECT

public:
    HarmonographApp(QWidget *parent = Q_NULLPTR);

private:
    HarmonographManager* manager;
    
    int const drawImgWidth = 1280;
    int const drawImgHeight = 720;
    float zoom = 100;

    Ui::HarmonographAppClass ui;

    QGraphicsView* view;
    CustomGraphicsView* customView;
    QGraphicsScene* scene;
    QTimer* autoRotationTimer;

    QCheckBox* ratioCheckBox;
    QComboBox* firstRatioValueCombo;
    QComboBox* secondRatioValueCombo;
    QLabel* colonLabel;

    QCheckBox* circleCheckBox;

    QDoubleSpinBox* freqPtSpinBox;
    QDoubleSpinBox* numOfPendulumsSpinBox;

    void redrawImage();

private slots:
    void updateImage();
    void autoRotate();
    void autoRotationTimerTimeout();
    void saveImage();
    void saveParametersToFile();
    void loadParametersFromFile();
    void ratioCheckBoxCliked(bool checked);
    void circleCheckBoxClicked(bool checked);
    void firstRatioPicked(const QString& text);
    void secondRatioPicked(const QString& text);
    void freqPointChanged(double freqPoint);
    void numOfPendulumsChanged(double newNum);

    void viewZoomChanged(int value);
};
