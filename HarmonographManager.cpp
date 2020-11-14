#include "HarmonographManager.h"

HarmonographManager::HarmonographManager() {
    harmonograph = new Harmonograph(3);
    imagePainter = new ImagePainter();
    imageSaver = new ImageSaver();
}

QGraphicsPixmapItem* HarmonographManager::getRenderedGraphicsItem() {
    Harmonograph* copyHarmongraph = new Harmonograph(harmonograph);
    return new QGraphicsPixmapItem(QPixmap::fromImage(imagePainter->getImage(copyHarmongraph)));
}

Harmonograph* HarmonographManager::getHarmCopy() {
    return new Harmonograph(harmonograph);
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
}

void HarmonographManager::changeSecondColor(QColor color) {
    imagePainter->secondColor = color;
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

void HarmonographManager::changePenWidth(int width) {
    imagePainter->penWidth = width;
}

void HarmonographManager::enableTwoColorMode(bool isEnabled) {
    imagePainter->useTwoColors = isEnabled;
}


void HarmonographManager::setFrequencyPoint(float freqPt) {
    if (freqPt > 0) harmonograph->changeFrequencyPointNoUpdate(freqPt);

}

void HarmonographManager::setNumOfPendulums(int newNum) {
    if (newNum > 0) harmonograph->setNumOfPendulums(newNum);
    harmonograph->update();
}

void HarmonographManager::undoUpdate() {
    if (history.size() > 0) {
        Harmonograph* undoHarm = new Harmonograph(history.back());
        history.pop_back();

        delete harmonograph;

        harmonograph = undoHarm;
    }
}

void HarmonographManager::changeParameter(int pendulumNum, HarmonographParameters parameter, int value) {
    float realValue;

    switch (parameter) {
        case HarmonographParameters::xPhase:
            realValue = (2 * pi / sliderMaxValue) * value;
            harmonograph->getPendulums().at(pendulumNum)->xPhase = realValue;
            break;

        case HarmonographParameters::xDamping:
            realValue = (maxDampingValue / sliderMaxValue) * value;
            harmonograph->getPendulums().at(pendulumNum)->xDumping = realValue;
            break;

        case HarmonographParameters::xFrequency:
            if(!harmonograph->isStar) realValue = (maxFreqModuleValue / (sliderMaxValue / 2)) * (value - (sliderMaxValue / 2)) + harmonograph->frequencyPoint;
            else realValue = (maxFreqModuleValue / (sliderMaxValue / 2)) * (value - (sliderMaxValue / 2)) + (harmonograph->frequencyPoint/(harmonograph->firstRatioValue+harmonograph->secondRatioValue)*(pendulumNum == 0 ? harmonograph->firstRatioValue : harmonograph->secondRatioValue));
            harmonograph->getPendulums().at(pendulumNum)->xFreq = realValue;
            harmonograph->getPendulums().at(pendulumNum)->xFrequencyNoise = (maxFreqModuleValue / (sliderMaxValue / 2)) * (value - (sliderMaxValue / 2));
            break;

        case HarmonographParameters::yPhase:
            realValue = (2 * pi / sliderMaxValue) * value;
            harmonograph->getPendulums().at(pendulumNum)->yPhase = realValue;
            break;

        case HarmonographParameters::yDamping:
            realValue = (maxDampingValue / sliderMaxValue) * value;
            harmonograph->getPendulums().at(pendulumNum)->yDumping = realValue;
            break;

        case HarmonographParameters::yFrequency:
            if (!harmonograph->isStar) realValue = (maxFreqModuleValue / (sliderMaxValue / 2)) * (value - (sliderMaxValue / 2)) + harmonograph->frequencyPoint;
            else realValue = (maxFreqModuleValue / (sliderMaxValue / 2)) * (value - (sliderMaxValue / 2)) + (harmonograph->frequencyPoint / (harmonograph->firstRatioValue + harmonograph->secondRatioValue) * (pendulumNum == 0 ? harmonograph->firstRatioValue : harmonograph->secondRatioValue));
            harmonograph->getPendulums().at(pendulumNum)->yFreq = realValue;
            harmonograph->getPendulums().at(pendulumNum)->yFrequencyNoise = (maxFreqModuleValue / (sliderMaxValue / 2)) * (value - (sliderMaxValue / 2));
            break;

        default:
            break;
    }
   
}
