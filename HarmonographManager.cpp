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
    harmonograph->update();
}

void HarmonographManager::changeXAxisRotation(float radians) {
    harmonograph->rotateXAxis(radians);
}

void HarmonographManager::saveCurrentImage(QString filename) {
    std::unique_ptr<ImagePainter> copyPainter(new ImagePainter(imagePainter));
    QImage imageToSave = copyPainter->getImageToSave(
        new Harmonograph(harmonograph),
        imageSaver->getSaveWidth(),
        imageSaver->getSaveHeight());

    imageSaver->saveImage(filename, imageToSave);
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
    imagePainter->zoom += value;
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
