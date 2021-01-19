#include "HarmonographManager.h"

HarmonographManager::HarmonographManager() {
    harmonograph = new Harmonograph(3);
    imageSaver = new HarmonographSaver();
}

Harmonograph* HarmonographManager::getHarmCopy() {
    return new Harmonograph(harmonograph);
}

float HarmonographManager::getCoordinateByTime(Dimension dimension, float t) {
    return harmonograph->getCoordinateByTime(dimension, t);
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

void HarmonographManager::saveCurrentImage(ImageSettings* settings){
    Harmonograph* copyHarm =new Harmonograph(harmonograph);
    DrawParameters params = drawParameters;
    params.penWidth = settings->penWidth;
    params.useAntiAliasing = settings->useAntialiasing;

    if (settings->transpBack) params.backgroundColor = QColor(0,0,0,0);

    imageSaver->saveImage(copyHarm, settings->filename, params, settings->saveWidth, settings->saveHeight);
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
    float temp = drawParameters.zoom + value;
    if (temp > 75 && temp < 200) {
        drawParameters.zoom += value;
    }
}

void HarmonographManager::changeFirstColor(QColor color) {
    drawParameters.firstColor = color;
}

void HarmonographManager::changeSecondColor(QColor color) {
    drawParameters.secondColor = color;
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
    drawParameters.penWidth = width;
}

void HarmonographManager::enableTwoColorMode(bool isEnabled) {
    drawParameters.useTwoColors = isEnabled;
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

void HarmonographManager::changeParameter(int pendulumNum, EquationParameter parameter, Dimension dimension, int value) {
    float realValue = 0;
    switch (parameter) {
    case EquationParameter::amplitude:
        break;
    case EquationParameter::dumping:
        realValue = (maxDampingValue / sliderMaxValue) * value;
        break;
    case EquationParameter::frequency:
        if (!harmonograph->isStar)
            realValue = 
            (maxFreqModuleValue / (sliderMaxValue / 2)) * (value - (sliderMaxValue / 2)) + harmonograph->frequencyPoint;
        else
            realValue =
            (maxFreqModuleValue / (sliderMaxValue / 2)) * (value - (sliderMaxValue / 2)) +
            (harmonograph->frequencyPoint / (harmonograph->firstRatioValue + harmonograph->secondRatioValue)
                * (pendulumNum == 0 ? harmonograph->firstRatioValue : harmonograph->secondRatioValue));

        harmonograph->getPendulums().at(pendulumNum)->setEquationParameter(dimension, EquationParameter::frequencyNoise, (maxFreqModuleValue / (sliderMaxValue / 2)) * (value - (sliderMaxValue / 2)));
        break;
    case EquationParameter::phase:
        realValue = (2 * pi / sliderMaxValue) * value;
        break;
    default:
        break;
    }

    harmonograph->getPendulums().at(pendulumNum)->setEquationParameter(dimension, parameter, realValue);
}
