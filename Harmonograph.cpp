#include "Harmonograph.h"


Harmonograph::Harmonograph(int n) {
	for (int i = 0; i < n; i++) {
		Pendulum *createdPendulum = new Pendulum();
		pendlums.push_back(createdPendulum);
	}
}

Harmonograph::Harmonograph(Harmonograph* harmonograph) {
	numOfPendulums = harmonograph->numOfPendulums;
	frequencyPoint = harmonograph->frequencyPoint;
	isStar = harmonograph->isStar;
	isCircle = harmonograph->isCircle;
	firstRatioValue = harmonograph->firstRatioValue;
	secondRatioValue = harmonograph->secondRatioValue;

	pendlums = harmonograph->getPundlumsCopy();
}

Harmonograph::Harmonograph(std::vector<Pendulum*> newPendulums, int firstRatioValue, int secondRatioValue, bool isStar, bool isCircle, float frequencyPoint) {
	pendlums = newPendulums;
	numOfPendulums = pendlums.size();

	this->firstRatioValue = firstRatioValue;
	this->secondRatioValue = secondRatioValue;
	this->isStar = isStar;
	this->isCircle = isCircle;
	this->frequencyPoint = frequencyPoint;
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
std::vector<Pendulum*> Harmonograph::getPundlumsCopy() {
	std::vector<Pendulum*> copies;
	for (Pendulum* p : pendlums) {
		copies.push_back(new Pendulum(p));
	}
	return copies;
}
void Harmonograph::update() {
	if (isStar && numOfPendulums > 1) {
		pendlums.at(0)->update((frequencyPoint / (firstRatioValue + secondRatioValue)) * firstRatioValue, isCircle);
		for (int i = 1; i < pendlums.size(); i++) {
			pendlums.at(i)->update((frequencyPoint / (firstRatioValue + secondRatioValue)) * secondRatioValue, isCircle);
		}
	}
	else {
		for (Pendulum* p : pendlums) {
			p->update(frequencyPoint, isCircle);
		}
	}
}

void Harmonograph::rotateXAxis(float radians)
{
	for (Pendulum* p : pendlums) {
		p->changeXPhase(radians);
	}
}

void Harmonograph::rotateXY(float x, float y) {
	pendlums.at(0)->changeXPhase(x);
	pendlums.at(0)->changeYPhase(y);
}

void Harmonograph::setNumOfPendulums(int newNum) {
	numOfPendulums = newNum;
	pendlums.clear();

	for (int i = 0; i < numOfPendulums; i++) {
		Pendulum* createdPendulum = new Pendulum();
		pendlums.push_back(createdPendulum);
	}
}
