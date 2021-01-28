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
#include <cmath>
#include <QRandomGenerator>


class PendulumDimension {
public:
	float const pi = atan(1) * 4;

	float amplitude = 1;
	float frequency = 0.1;
	float phase = 0;
	float dumping = 0.1;

	float frequencyNoise = 0.1;

	PendulumDimension(float frequencyPoint, bool isCircle, int circleRandomValue);
	PendulumDimension(float amplitude, float frequency, float phase, float dumping, float frequencyNoise);

	void update(float frequencyPoint, bool isCircle, int circleRandomValue);
	void updateFrequencyPoint(float FrequencyPoint);
	PendulumDimension* getDimensionCopy() {
		return new PendulumDimension(amplitude, frequency, phase, dumping, frequencyNoise);
	}
};

