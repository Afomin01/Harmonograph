#pragma once

#include <cstdlib>
#include <cmath>
#include <time.h>
#include "Dimension.h"
#include "PendulumDemension.h"
#include "PendulumEquationParametersEnum.h"

class Pendulum {
public:
	Pendulum(Pendulum* pendulum);
	Pendulum();
	Pendulum(std::vector<PendulumDemension*> dimensions);
	Pendulum(int dimensionsCount, float frequencyPoint, bool isCircle);
	~Pendulum() {
	}

	std::vector<PendulumDemension*> getDimensionsCopy();

	float getCoordinateByTime(Dimension dimension, float t);

	void update(float frequencyPoint, bool isCircle);

	void changeDimensionEquationPhase(Dimension dimension, float radians);

	void updateFrequencyPoint(float frequencyPoint);

	float getEquationParameter(Dimension dimension, EquationParameter parameter);
	void setEquationParameter(Dimension dimension, EquationParameter parameter, float value);

private:
	std::vector<PendulumDemension*> dimensions;
};

