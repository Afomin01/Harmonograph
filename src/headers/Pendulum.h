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

#include <cstdlib>
#include <cmath>
#include <time.h>
#include "Dimension.h"
#include "PendulumDimension.h"
#include "PendulumEquationParametersEnum.h"
#include <QRandomGenerator>

class Pendulum {
public:
	Pendulum(Pendulum* pendulum);
	Pendulum();
	Pendulum(std::vector<PendulumDimension*> dimensions);
	Pendulum(int dimensionsCount, float frequencyPoint, bool isCircle);
	~Pendulum(){
		
	}

	std::vector<PendulumDimension*> getDimensionsCopy();

	float getCoordinateByTime(Dimension dimension, float t);

	void update(float frequencyPoint, bool isCircle);

	void changeDimensionEquationPhase(Dimension dimension, float radians);

	void updateFrequencyPoint(float frequencyPoint);

	float getEquationParameter(Dimension dimension, EquationParameter parameter);
	void setEquationParameter(Dimension dimension, EquationParameter parameter, float value);

private:
	std::vector<PendulumDimension*> dimensions;
};

