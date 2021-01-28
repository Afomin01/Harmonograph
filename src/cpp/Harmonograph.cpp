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

#include "Harmonograph.h"


Harmonograph::Harmonograph(int numOfPendulums) {
	for (int i = 0; i < numOfPendulums; i++) {
		Pendulum *createdPendulum = new Pendulum();
		pendlums.push_back(createdPendulum);
	}
	this->numOfPendulums = numOfPendulums;
}

Harmonograph::Harmonograph(Harmonograph* harmonograph) {
	numOfPendulums = harmonograph->numOfPendulums;
	frequencyPoint = harmonograph->frequencyPoint;
	isStar = harmonograph->isStar;
	isCircle = harmonograph->isCircle;
	firstRatioValue = harmonograph->firstRatioValue;
	secondRatioValue = harmonograph->secondRatioValue;

	pendlums = harmonograph->getPundlumsCopy();
}

Harmonograph::Harmonograph(std::vector<Pendulum*> newPendulums, int firstRatioValue, int secondRatioValue, bool isStar, bool isCircle, float frequencyPoint) {
	pendlums = newPendulums;
	numOfPendulums = pendlums.size();

	this->firstRatioValue = firstRatioValue;
	this->secondRatioValue = secondRatioValue;
	this->isStar = isStar;
	this->isCircle = isCircle;
	this->frequencyPoint = frequencyPoint;
}

Harmonograph::~Harmonograph() {
}

float Harmonograph::getCoordinateByTime(Dimension demension, float t) {
	float c = 0;

	for (Pendulum* p : pendlums) {
		c += p->getCoordinateByTime(demension, t);
	}
	return c;
}

std::vector<Pendulum*> Harmonograph::getPundlumsCopy() {
	std::vector<Pendulum*> copies;
	for (Pendulum* p : pendlums) {
		copies.push_back(new Pendulum(p));
	}
	return copies;
}
void Harmonograph::update() {
	if (isStar && numOfPendulums > 1) {
		pendlums.at(0)->update((frequencyPoint / (firstRatioValue + secondRatioValue)) * firstRatioValue, isCircle);
		for (int i = 1; i < pendlums.size(); i++) {
			pendlums.at(i)->update((frequencyPoint / (firstRatioValue + secondRatioValue)) * secondRatioValue, isCircle);
		}
	}
	else {
		for (Pendulum* p : pendlums) {
			p->update(frequencyPoint, isCircle);
		}
	}
}

void Harmonograph::rotateXAxis(float radians)
{
	for (Pendulum* p : pendlums) {
		p->changeDimensionEquationPhase(Dimension::x, radians);
	}
}

void Harmonograph::rotateXY(float x, float y) {
	pendlums.at(0)->changeDimensionEquationPhase(Dimension::x, x);
	pendlums.at(0)->changeDimensionEquationPhase(Dimension::y, y);
}

void Harmonograph::setNumOfPendulums(int newNum) {
	numOfPendulums = newNum;
	pendlums.clear();

	for (int i = 0; i < numOfPendulums; i++) {
		Pendulum* createdPendulum = new Pendulum();
		pendlums.push_back(createdPendulum);
	}
}

void Harmonograph::changeFrequencyPointNoUpdate(float newFrequecnyPoint) {
	frequencyPoint = newFrequecnyPoint;
	if (isStar && numOfPendulums > 1) {
		pendlums.at(0)->updateFrequencyPoint((frequencyPoint / (firstRatioValue + secondRatioValue)) * firstRatioValue);
		for (int i = 1; i < pendlums.size(); i++) {
			pendlums.at(i)->updateFrequencyPoint((frequencyPoint / (firstRatioValue + secondRatioValue)) * secondRatioValue);
		}
	}
	else {
		for (Pendulum* p : pendlums) {
			p->updateFrequencyPoint(frequencyPoint);
		}
	}
}
