#pragma once

#include <cstdlib>
#include <cmath>
#include <time.h> 

class Pendulum
{
public:
	float const pi = atan(1) * 4;

	Pendulum() {
		srand(unsigned int(time(NULL)));
		xDumping = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02)));
		xPhase = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (pi)));
		xFreq = 2 + 1e-01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
		xAmplitude = 1;

		yDumping = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02)));
		yPhase = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (pi)));
		yFreq = 2 + 1e-01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1e-02 - 1e-01)));
		yAmplitude = 1;
	};
	~Pendulum() {
	}

	float getX(float t);
	float getY(float t);

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

