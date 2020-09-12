#include "Pendulum.h"



float Pendulum::getX(float t) {
	return exp(-xDumping * t) * cos(xFreq * t + xPhase);
}
float Pendulum::getY(float t) {
	return exp(-yDumping * t) * sin(yFreq * t + yPhase);
}
void Pendulum::update() {

	//srand(unsigned int(time(NULL)));
	xDumping = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02)));
	xPhase = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (pi)));
	xFreq = 2 + 1e-01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
	xAmplitude = 1;

	yDumping = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02)));
	yPhase = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (pi)));
	yFreq = 2 + 1e-01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
	yAmplitude = 1;

	//int r = rand();
	//xDumping = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02)));
	//xPhase = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (pi)));
	//xFreq = 2 + 1e-01 + static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
	//xAmplitude = 1;

	//yDumping = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02)));
	//yPhase = static_cast <float> (r) / (static_cast <float> (RAND_MAX / (pi)));
	//yFreq = 2 + 1e-01 + static_cast <float> (r) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
	//yAmplitude = 1;
}
void Pendulum::changeXPhase(float radians)
{
	xPhase += radians;
}
void Pendulum::changeYPhase(float radians)
{
	yPhase += radians;
}
Pendulum::Pendulum() {
	srand(unsigned int(time(NULL)));
	xDumping = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02)));
	xPhase = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (pi)));
	xFreq = 2 + 1e-01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
	xAmplitude = 1;

	yDumping = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02)));
	yPhase = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (pi)));
	yFreq = 2 + 1e-01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
	yAmplitude = 1;
}