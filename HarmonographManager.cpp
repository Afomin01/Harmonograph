#include "HarmonographManager.h"

HarmonographManager::HarmonographManager() {
    harmonograph = new Harmonograph(3);
    imagePainter = new ImagePainter();
    imageSaver = new ImageSaver();
}

QGraphicsPixmapItem* HarmonographManager::getRenderedGraphicsItem() {
    return new QGraphicsPixmapItem(QPixmap::fromImage(imagePainter->getImage(harmonograph)));
}

void HarmonographManager::updateRandomValues() {
    history.push_back(new Harmonograph(harmonograph));
    harmonograph->update();
    if (history.size() > 10) {
        history.pop_front();
    }
}

void HarmonographManager::changeXAxisRotation(float radians) {
    harmonograph->rotateXAxis(radians);
}

void HarmonographManager::rotateXY(float x, float y) {
    harmonograph->rotateXY(x, y);
}

void HarmonographManager::saveCurrentImage(QString filename) {
    imageSaver->saveImage(new Harmonograph(harmonograph), filename, new ImagePainter(imagePainter));
}
void HarmonographManager::saveParametersToFile(QString filename) {
    Harmonograph* copyHarmonograph = new Harmonograph(harmonograph);
    imageSaver->saveParametersToFile(filename, copyHarmonograph);
}

void HarmonographManager::loadParametersFromFile(QString filename) {
    Harmonograph* loadedHarmonograph = imageSaver->loadParametersFromFile(filename);
    if (loadedHarmonograph != nullptr) {
        delete harmonograph;
        harmonograph = loadedHarmonograph;
    }
}

void HarmonographManager::changeZoom(float value) {
    float temp = imagePainter->zoom + value;
    if (temp > 75 && temp < 200) {
        imagePainter->zoom += value;
    }
}

void HarmonographManager::changeFirstColor(QColor color) {
    imagePainter->firstColor = color;
    harmonograph->update();
}

void HarmonographManager::changeSecondColor(QColor color) {
    imagePainter->secondColor = color;
    harmonograph->update();
}

void HarmonographManager::ratioStateEnabled(bool isEnabled) {
    harmonograph->isStar = isEnabled;
    harmonograph->update();
}

void HarmonographManager::changeFirstRatioValue(int value) {
    if (value > 0) {
        harmonograph->firstRatioValue = value;
        harmonograph->update();
    }
}

void HarmonographManager::changeSecondRatioValue(int value) {
    if (value > 0) {
        harmonograph->secondRatioValue = value;
        harmonograph->update();
    }
}

void HarmonographManager::circleStateEnabled(bool isEnabled) {
    harmonograph->isCircle = isEnabled;
    harmonograph->update();
}

void HarmonographManager::enableTwoColorMode(bool isEnabled) {
    imagePainter->useTwoColors = isEnabled;
    harmonograph->update();
}


void HarmonographManager::setFrequencyPoint(float freqPt) {
    if (freqPt > 0) harmonograph->frequencyPoint = freqPt;
    harmonograph->update();
}

void HarmonographManager::setNumOfPendulums(int newNum) {
    if (newNum > 0) harmonograph->setNumOfPendulums(newNum);
    harmonograph->update();
}
