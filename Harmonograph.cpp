#include "Harmonograph.h"


Harmonograph::Harmonograph(int n) {
	for (int i = 0; i < n; i++) {
		Pendulum *createdPendulum = new Pendulum();
		pendlums.push_back(createdPendulum);
	}
}

Harmonograph::~Harmonograph() {
	for(Pendulum *p : pendlums){
		delete p;
	}
}

float Harmonograph::getX(float t) {
	float x = 0;

	for (Pendulum *p : pendlums) {
		x+=p->getX(t);
	}
	return x;
}
float Harmonograph::getY(float t) {
	float y = 0;

	for (Pendulum* p : pendlums) {
		y += p->getY(t);
	}
	return y;
}