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
	PendulumDimension* getDemensionCopy() {
		return new PendulumDimension(amplitude, frequency, phase, dumping, frequencyNoise);
	}
};

