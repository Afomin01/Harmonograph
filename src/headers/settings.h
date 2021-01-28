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
#include <QtWidgets>
#include "Harmonograph.h"
#include "FlexModesEnum.h"
#include "DrawParameteres.h"

class FlexSettings {
public:
	Harmonograph* flexGraph = nullptr;
	FlexModes flexBaseMode = FlexModes::phaseBased;
	int FPSLimit = 60;
	DrawParameters parameters;
};

class ImageSettings {
public:
	DrawParameters parameters;
	QString filename = "";
	bool useSquareImage = false;
	int borderPercentage = 3;
	int saveWidth = 1920;
	int saveHeight = 1080;
};

class ColorTemplate {
public:
	ColorTemplate(QColor primary, QColor secondary, QColor background);
	ColorTemplate() = default;

	QColor primaryColor = Qt::blue;
	QColor secondaryColor = Qt::red;
	QColor backgroundColor = Qt::white;
};

class NamedColorTemplate {
public:
	NamedColorTemplate(long long id, QString filename, QString name, ColorTemplate colorTemplate);

	long long id = 0;
	QString filename = "";
	QString name = "";
	ColorTemplate colorTemplate;
};
