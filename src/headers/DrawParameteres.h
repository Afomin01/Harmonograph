/*
 *   Copyright 2020-2021 Artem Bakin and Dmitriy Kuperstein
 *
 *   This file is part of Harmonograph.
 *
 *   Harmonograph is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Harmonograph is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Harmonograph.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#pragma once
#include <QColor>


enum class DrawModes {
	linesMode,
	pointsMode
};

class DrawParameters{
public:
	bool useTwoColors = true;
	bool useAntiAliasing = true;
	DrawModes drawMode = DrawModes::linesMode;
	int penWidth = 1;
	float zoom = 0.25;
	float timeStep = 0.01;
	
	QColor primaryColor = Qt::blue;
	QColor secondColor = Qt::red;
	QColor backgroundColor = Qt::white;
};


