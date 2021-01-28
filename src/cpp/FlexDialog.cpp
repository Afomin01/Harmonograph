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

#include "FlexDialog.h"

FlexDialog::FlexDialog(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);
	useAntiAliasing = ui.antialiasingCheckBox->isChecked();
	FPS = ui.FPSSpinBox->value();
}

FlexDialog::~FlexDialog(){
}

void FlexDialog::changeBase(int value) {
	if(value==0){
		flexBaseMode = FlexModes::phaseBased;
	}
	else if(value==1){
		flexBaseMode = FlexModes::frequencyBased;
	}
}

void FlexDialog::useAntialiasingState(int state) {
	useAntiAliasing = state == 2;
}

void FlexDialog::setFPS(int value) {
	FPS = value;
}