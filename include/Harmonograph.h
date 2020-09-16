#pragma once

#include "Pendulum.h"
#include <vector>
#include <cmath>

class Harmonograph
{ 
public:
	int numOfPendulums = 3;
	float frequencyPoint = 2;
	bool isStar = false;
	bool isCircle = false;
	int firstRatioValue = 1;
	int secondRatioValue = 1;

	Harmonograph(int n);
	Harmonograph(Harmonograph* harmonograph);
	Harmonograph(std::vector<Pendulum*> pendulums, int firstRatioValue, int secondRatioValue, bool isStar, bool isCircle, float frequencyPoint);
	Harmonograph();
	~Harmonograph();

	float getX(float t);
	float getY(float t);
	std::vector<Pendulum*> getPundlumsCopy();
	void update();
	void rotateXAxis(float radians);

private:
	std::vector<Pendulum*> pendlums;

};


