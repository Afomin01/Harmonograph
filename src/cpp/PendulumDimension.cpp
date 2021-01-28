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

#include "PendulumDimension.h"

PendulumDimension::PendulumDimension(float frequencyPoint, bool isCircle, int circleRandomValue) {
	update(frequencyPoint, isCircle, circleRandomValue );
}

PendulumDimension::PendulumDimension(float amplitude, float frequency, float phase, float dumping, float frequencyNoise) {
	this->amplitude = amplitude;
	this->frequency = frequency;
	this->phase = phase;
	this->dumping = dumping;

	this->frequencyNoise = frequencyNoise;
}

void PendulumDimension::update(float frequencyPoint, bool isCircle, int circleRandomValue) {
	if (!isCircle) {
		dumping = QRandomGenerator::global()->bounded(1e-02);
		phase = QRandomGenerator::global()->bounded(pi);
		frequencyNoise = QRandomGenerator::global()->bounded(1e-02 - 1e-01);
		frequency = frequencyPoint + frequencyNoise;
		amplitude = 1;
	}
	else {
		dumping = static_cast <float> (circleRandomValue) / (static_cast <float> (RAND_MAX / (1e-02)));
		phase = static_cast <float> (circleRandomValue) / (static_cast <float> (RAND_MAX / (pi)));
		frequencyNoise = static_cast <float> (circleRandomValue) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
		frequency = frequencyPoint + frequencyNoise;
		amplitude = 1;
	}
}

void PendulumDimension::updateFrequencyPoint(float FrequencyPoint) {
	frequency = frequencyNoise + FrequencyPoint;
}
