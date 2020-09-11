#include "Pendulum.h"



float Pendulum::getX(float t) {
	return exp(-xDumping * t) * cos(xFreq * t + xPhase);
}
float Pendulum::getY(float t) {
	return exp(-yDumping * t) * sin(yFreq * t + yPhase);
}