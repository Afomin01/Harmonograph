#include "Pendulum.h"
#include <QRandomGenerator>

float Pendulum::getX(float t) {
	return exp(-xDumping * t) * cos(xFreq * t + xPhase);
}
float Pendulum::getY(float t) {
	return exp(-yDumping * t) * sin(yFreq * t + yPhase);
}
void Pendulum::update(float frequencyPoint, bool isCircle) {

	if (!isCircle) {
		xDumping = QRandomGenerator::global()->bounded(1e-02);
		xPhase = QRandomGenerator::global()->bounded(pi);
		xFrequencyNoise = QRandomGenerator::global()->bounded(1e-02 - 1e-01) + 1e-01;
		xFreq = frequencyPoint + xFrequencyNoise;
		xAmplitude = 1;

		yDumping = QRandomGenerator::global()->bounded(1e-02);
		yPhase = QRandomGenerator::global()->bounded(pi);
		yFrequencyNoise = QRandomGenerator::global()->bounded(1e-02 - 1e-01) + 1e-01;
		yFreq = frequencyPoint + yFrequencyNoise;
		yAmplitude = 1;
	}
	else {
		int r = rand();
		xDumping = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02)));
		xPhase = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (pi)));
		xFrequencyNoise = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01))) + 1e-01;
		xFreq = frequencyPoint + xFrequencyNoise;
		xAmplitude = 1;

		yDumping = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02)));
		yPhase = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (pi)));
		yFrequencyNoise = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01))) + 1e-01;
		yFreq = frequencyPoint + yFrequencyNoise;
		yAmplitude = 1;
	}
}
void Pendulum::changeXPhase(float radians)
{
	xPhase += radians;
}
void Pendulum::changeYPhase(float radians)
{
	yPhase += radians;
}
void Pendulum::updateFrequencyPoint(float frequencyPoint) {
	xFreq = xFrequencyNoise + frequencyPoint;
	yFreq = yFrequencyNoise + frequencyPoint;
}
Pendulum::Pendulum(Pendulum* pendulum) {
	xDumping = pendulum->xDumping;
	xPhase = pendulum->xPhase;
	xFreq = pendulum->xFreq;
	xFrequencyNoise = pendulum->xFrequencyNoise;
	xAmplitude = pendulum->xAmplitude;

	yDumping = pendulum->yDumping;
	yPhase = pendulum->yPhase;
	yFreq = pendulum->yFreq;
	yFrequencyNoise = pendulum->yFrequencyNoise;
	yAmplitude = pendulum->yAmplitude;
}
Pendulum::Pendulum(float xDamp, float xPhase, float xFreq, float xFreqNoise, float xAmpl, float yDamp, float yPhase, float yFreq, float yFreqNoise, float yAmpl) {
	this->xDumping = xDamp;
	this->xPhase = xPhase;
	this->xFreq = xFreq;
	this->xAmplitude = xAmpl;

	this->yDumping = yDamp;
	this->yPhase = yPhase;
	this->yFreq = yFreq;
	this->yAmplitude = yAmpl;
}
Pendulum::Pendulum() {
	this->update(2, false);
}

Pendulum::Pendulum(float frequencyPoint, bool isCircle) {
	this->update(frequencyPoint, isCircle);
}
