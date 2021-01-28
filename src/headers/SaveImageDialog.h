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

#include <QDialog>
#include <ui_SaveImageDialog.h>

class SaveImageDialog : public QDialog
{
	Q_OBJECT

public:
	SaveImageDialog(QWidget *parent = Q_NULLPTR);
	~SaveImageDialog();

	bool useAntialiasing = false;
	bool useSquareImage = false;
	bool transpBack = false;
	int saveWidth = 1920;
	int saveHeight = 1080;
	int penWidth = 1;
	int borderPercentage = 3;

private:
	Ui::SaveImageDialog ui;
private slots:
	virtual void accept();
};
