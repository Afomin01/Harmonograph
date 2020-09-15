#include "Pendulum.h"



float Pendulum::getX(float t) {
	return exp(-xDumping * t) * cos(xFreq * t + xPhase);
}
float Pendulum::getY(float t) {
	return exp(-yDumping * t) * sin(yFreq * t + yPhase);
}
void Pendulum::update(float frequencyPoint, bool isCircle, bool isStar, int firstRatioValue, int secondRatioValue) {

	if (!isCircle) {
		xDumping = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02)));
		xPhase = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (pi)));
		xFreq = frequencyPoint + 1e-01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
		xAmplitude = 1;

		yDumping = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02)));
		yPhase = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (pi)));
		yFreq = 2 + 1e-01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
		yAmplitude = 1;
	}
	else {
		int r = rand();
		xDumping = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02)));
		xPhase = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (pi)));
		xFreq = frequencyPoint + 1e-01 + static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
		xAmplitude = 1;

		yDumping = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02)));
		yPhase = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (pi)));
		yFreq = 2 + 1e-01 + static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
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
Pendulum::Pendulum(Pendulum* pendulum) {
	xDumping = pendulum->xDumping;
	xPhase = pendulum->xPhase;
	xFreq = pendulum->xFreq;
	xAmplitude = pendulum->xAmplitude;

	yDumping = pendulum->yDumping;
	yPhase = pendulum->yPhase;
	yFreq = pendulum->yFreq;
	yAmplitude = pendulum->yAmplitude;
}
Pendulum::Pendulum(float xDamp, float xPhase, float xFreq, float xAmpl, float yDamp, float yPhase, float yFreq, float yAmpl) {
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
	//srand(unsigned int(time(NULL)));
	xDumping = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02)));
	xPhase = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (pi)));
	xFreq = 2 + 1e-01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
	xAmplitude = 1;

	yDumping = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02)));
	yPhase = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (pi)));
	yFreq = 2 + 1e-01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
	yAmplitude = 1;
}