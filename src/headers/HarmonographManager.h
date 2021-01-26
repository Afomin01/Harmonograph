#pragma once
#include <QtWidgets>
#include "Harmonograph.h"
#include "HarmonographSaver.h"
#include "settings.h"
#include "PendulumEquationParametersEnum.h"
#include "Dimension.h"
#include <deque>
#include <cmath>
#include "DrawParameteres.h"

class HarmonographManager{
public:	
	float const pi = atan(1) * 4;
	float const maxDampingValue = 0.01;
	float const maxFreqModuleValue = 0.1;
	int const sliderMaxValue = 150;

	HarmonographManager();
	HarmonographManager(Harmonograph* harm);
	~HarmonographManager();

	Harmonograph* getHarmCopy();

	void updateRandomValues();

	void changeXAxisRotation(float radians);
	void rotateXY(float x, float y);

	void saveCurrentImage(ImageSettings* settings);

	void saveParametersToFile(QString filename);
	void loadParametersFromFile(QString filename);

	void setRatioStateEnabled(bool isEnabled);
	void setFirstRatioValue(int value);
	void setSecondRatioValue(int value);

	void setIsCircleEnabled(bool isEnabled);

	void setFrequencyPoint(float freqPt);
	void setNumOfPendulums(int newNum);

	float getCoordinateByTime(Dimension dimension, float t);

	void changeParameter(int pendulumNum, EquationParameter parameter, Dimension dimension, int value);
	
	void undoUpdate();

	DrawParameters getDrawParameters();

	void setUseTwoColors(bool isEnabled);
	void setPrimaryColor(QColor color);
	void setSecondColor(QColor color);
	void setBackgroundColor(QColor color);
	void setPenWidth(int width);
	void setZoom(float value);
	void setDrawMode(DrawModes mode);
	void setDrawParameters(DrawParameters parameters);
	void setTimeStep(double step);

	int getHistorySize();
	std::vector<Pendulum*> getPendulumsCopy();

private:
	Harmonograph* harmonograph;
	HarmonographSaver* harmonographSaver;
	std::deque<Harmonograph*> history;
	DrawParameters drawParameters = DrawParameters();
};
