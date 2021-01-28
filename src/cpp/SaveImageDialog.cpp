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

#include "SaveImageDialog.h"

SaveImageDialog::SaveImageDialog(QWidget *parent): QDialog(parent){
	ui.setupUi(this);
	saveWidth = 1920;
	saveHeight = 1080;
}

SaveImageDialog::~SaveImageDialog(){
	
}


void SaveImageDialog::accept() {
	useSquareImage = ui.useSquareImageCheckBox->checkState() == 2;

	QString str;
	if (useSquareImage) str = ui.squareResComboBox->currentText();
	else str = ui.regularResComboBox->currentText();

	saveWidth = str.split("x").at(0).toInt();
	saveHeight = str.split("x").at(1).toInt();

	useAntialiasing = ui.useAntialiasingCheckBox->checkState() == 2;

	transpBack = ui.transpBackCheckBox->checkState() == 2;

	penWidth = ui.penWidthSpinBox->value();

	borderPercentage = ui.borderPercentageSpinBox->value();

	QDialog::accept();
}