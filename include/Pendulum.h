#pragma once

#include <cstdlib>
#include <cmath>
#include <time.h> 

class Pendulum
{
public:
	float const pi = atan(1) * 4;

	float xDumping = 0.1;
	float xPhase = 0;
	float xFreq = 0.1;
	float xAmplitude = 1;

	float yDumping = 0.1;
	float yPhase = 0;
	float yFreq = 0.1;
	float yAmplitude = 1;

	float xFrequencyNoise = 0.1;
	float yFrequencyNoise = 0.1;

	Pendulum(Pendulum* pendulum);
	Pendulum(float xDamp, float xPhase, float xFreq, float xFreqNoise, float xAmpl, float yDamp, float yPhase, float yFreq, float yFreqNoise, float yAmpl);
	Pendulum();
	Pendulum(float frequencyPoint, bool isCircle);
	~Pendulum() {
	}

	float getX(float t);
	float getY(float t);
	void update(float frequencyPoint, bool isCircle);
	void changeXPhase(float radians);
	void changeYPhase(float radians);
	void updateFrequencyPoint(float frequencyPoint);

private:
};

