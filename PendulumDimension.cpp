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
