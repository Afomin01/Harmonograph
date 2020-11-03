#pragma once

#include "Pendulum.h"
#include <vector>
#include <cmath>

class Harmonograph
{ 
public:
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


