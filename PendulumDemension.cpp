#include "PendulumDemension.h"

PendulumDemension::PendulumDemension(float frequencyPoint, bool isCircle) {
	update(frequencyPoint, isCircle);
}

PendulumDemension::PendulumDemension(float amplitude, float frequency, float phase, float dumping, float frequencyNoise) {
	this->amplitude = amplitude;
	this->frequency = frequency;
	this->phase = phase;
	this->dumping = dumping;

	this->frequencyNoise = frequencyNoise;
}

void PendulumDemension::update(float frequencyPoint, bool isCircle) {
	if (!isCircle) {
		dumping = QRandomGenerator::global()->bounded(1e-02);
		phase = QRandomGenerator::global()->bounded(pi);
		frequencyNoise = QRandomGenerator::global()->bounded(1e-02 - 1e-01);
		frequency = frequencyPoint + frequencyNoise;
		amplitude = 1;
	}
	else {
		int r = rand();
		dumping = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02)));
		phase = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (pi)));
		frequencyNoise = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
		frequency = frequencyPoint + frequencyNoise;
		amplitude = 1;
	}
}

void PendulumDemension::updateFrequencyPoint(float FrequencyPoint) {
	frequency = frequencyNoise + FrequencyPoint;
}
