#pragma once

#include "Pendulum.h"
#include <vector>
#include <cmath>
#include "Dimension.h"

class Harmonograph
{ 
public:
	float frequencyPoint = 2;
	float frequenyNoise = 0.1;
	bool isStar = false;
	bool isCircle = false;
	int firstRatioValue = 1;
	int secondRatioValue = 1;

	Harmonograph(int n);
	Harmonograph(Harmonograph* harmonograph);
	Harmonograph(std::vector<Pendulum*> pendulums, int firstRatioValue, int secondRatioValue, bool isStar, bool isCircle, float frequencyPoint);
	Harmonograph();
	~Harmonograph();

	float getCoordinateByTime(Dimension demension, float t);

	int getNumOfPendulums() {
		return numOfPendulums;
	}
	std::vector<Pendulum*> getPundlumsCopy();
	void update();
	void rotateXAxis(float radians);
	void rotateXY(float x, float y);
	void setNumOfPendulums(int newNum);
	void changeFrequencyPointNoUpdate(float newFrequecnyPoint);

	std::vector<Pendulum*> getPendulums() {
		return pendlums;
	}
	
private:
	int numOfPendulums = 3;
	std::vector<Pendulum*> pendlums;

};


