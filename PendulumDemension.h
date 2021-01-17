#pragma once
#include <cmath>
#include <QRandomGenerator>


class PendulumDemension {
public:
	float const pi = atan(1) * 4;

	float amplitude = 1;
	float frequency = 0.1;
	float phase = 0;
	float dumping = 0.1;

	float frequencyNoise = 0.1;

	PendulumDemension(float frequencyPoint, bool isCircle);
	PendulumDemension(float amplitude, float frequency, float phase, float dumping, float frequencyNoise);

	void update(float frequencyPoint, bool isCircle);
	void updateFrequencyPoint(float FrequencyPoint);
	PendulumDemension* getDemensionCopy() {
		return new PendulumDemension(amplitude, frequency, phase, dumping, frequencyNoise);
	}
};

