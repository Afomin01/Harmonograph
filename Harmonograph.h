#pragma once

#include "Pendulum.h"
#include <vector>
#include <cmath>

class Harmonograph
{ 
public:
	Harmonograph(int n);
	Harmonograph();
	~Harmonograph();

	float getX(float t);
	float getY(float t);
	void update();
	void rotateXAxis(float radians);

private:
	std::vector<Pendulum*> pendlums;

};


