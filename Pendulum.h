#pragma once

#include <cstdlib>
#include <cmath>
#include <time.h> 

class Pendulum
{
public:
	float const pi = atan(1) * 4;

	Pendulum();
	~Pendulum() {
	}

	float getX(float t);
	float getY(float t);
	void update();
	void changeXPhase(float radians);
	void changeYPhase(float radians);

private:
	float xDumping = 0.1;
	float xPhase = 0;
	float xFreq = 0.1;
	float xAmplitude = 1;

	float yDumping = 0.1;
	float yPhase = 0;
	float yFreq = 0.1;
	float yAmplitude = 1;
};

