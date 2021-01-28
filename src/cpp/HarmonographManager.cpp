/*
 *   Copyright 2020-2021 Artem Bakin and Dmitriy Kuperstein
 *
 *   This file is part of Harmonograph.
 *
 *   Harmonograph is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Harmonograph is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Harmonograph.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "HarmonographManager.h"

HarmonographManager::HarmonographManager() {
    harmonograph = new Harmonograph(3);
    harmonographSaver = new HarmonographSaver();
}

HarmonographManager::HarmonographManager(Harmonograph* harm) {
    this->harmonograph = harm;
    harmonographSaver = new HarmonographSaver();
}

HarmonographManager::~HarmonographManager() {
    delete harmonograph;
	delete harmonographSaver;
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
    Harmonograph* copyHarm = new Harmonograph(harmonograph);

    harmonographSaver->saveImage(copyHarm, settings);
}
void HarmonographManager::saveParametersToFile(QString filename) {
    Harmonograph* copyHarmonograph = new Harmonograph(harmonograph);
    harmonographSaver->saveParametersToFile(filename, copyHarmonograph);
}

void HarmonographManager::loadParametersFromFile(QString filename) {
    Harmonograph* loadedHarmonograph = harmonographSaver->loadParametersFromFile(filename);
    if (loadedHarmonograph != nullptr) {
        delete harmonograph;
        harmonograph = loadedHarmonograph;
    }
}

void HarmonographManager::setPrimaryColor(QColor color) {
    drawParameters.primaryColor = color;
}

int HarmonographManager::getHistorySize() {
    return history.size();
}

std::vector<Pendulum*> HarmonographManager::getPendulumsCopy() {
    return harmonograph->getPundlumsCopy();
}

void HarmonographManager::setSecondColor(QColor color) {
    drawParameters.secondColor = color;
}

void HarmonographManager::setBackgroundColor(QColor color) {
    drawParameters.backgroundColor = color;
}

void HarmonographManager::setRatioStateEnabled(bool isEnabled) {
    harmonograph->isStar = isEnabled;
    harmonograph->update();
}

void HarmonographManager::setFirstRatioValue(int value) {
    if (value > 0) {
        harmonograph->firstRatioValue = value;
        harmonograph->update();
    }
}

void HarmonographManager::setSecondRatioValue(int value) {
    if (value > 0) {
        harmonograph->secondRatioValue = value;
        harmonograph->update();
    }
}

void HarmonographManager::setIsCircleEnabled(bool isEnabled) {
    harmonograph->isCircle = isEnabled;
    harmonograph->update();
}

void HarmonographManager::setPenWidth(int width) {
    drawParameters.penWidth = width;
}

void HarmonographManager::setZoom(float value) {
    drawParameters.zoom = value;
}

void HarmonographManager::setDrawMode(DrawModes mode) {
    drawParameters.drawMode = mode;
}

void HarmonographManager::setDrawParameters(DrawParameters parameters) {
    drawParameters = parameters;
}

void HarmonographManager::setTimeStep(double step) {
    drawParameters.timeStep = step;
}

void HarmonographManager::setUseTwoColors(bool isEnabled) {
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

DrawParameters HarmonographManager::getDrawParameters() {
    return drawParameters;
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
