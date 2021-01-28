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
#include "ui_FlexDialog.h"
#include "FlexWindow.h"


class FlexDialog : public QDialog
{
	Q_OBJECT

public:
	FlexDialog(QWidget* parent = Q_NULLPTR);
	~FlexDialog();

	int FPS = 60;
	bool useAntiAliasing = true;
	FlexModes flexBaseMode = FlexModes::phaseBased;

private:
	Ui::FlexDialog ui;
private slots:
	void changeBase(int value);
	void useAntialiasingState(int state);
	void setFPS(int value);
};
