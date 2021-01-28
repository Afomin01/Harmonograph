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

#pragma once

#include "Pendulum.h"
#include <vector>
#include <cmath>
#include "Dimension.h"

class Harmonograph
{ 
public:
	float frequencyPoint = 2;
	float frequenyNoise = 0.1;
	bool isStar = false;
	bool isCircle = false;
	int firstRatioValue = 1;
	int secondRatioValue = 1;

	Harmonograph(int numOfPendulums);
	Harmonograph(Harmonograph* harmonograph);
	Harmonograph(std::vector<Pendulum*> pendulums, int firstRatioValue, int secondRatioValue, bool isStar, bool isCircle, float frequencyPoint);
	Harmonograph();
	~Harmonograph();

	float getCoordinateByTime(Dimension demension, float t);

	int getNumOfPendulums() {
		return numOfPendulums;
	}
	std::vector<Pendulum*> getPundlumsCopy();
	void update();
	void rotateXAxis(float radians);
	void rotateXY(float x, float y);
	void setNumOfPendulums(int newNum);
	void changeFrequencyPointNoUpdate(float newFrequecnyPoint);

	std::vector<Pendulum*> getPendulums() {
		return pendlums;
	}
	
private:
	int numOfPendulums = 3;
	std::vector<Pendulum*> pendlums;

};


