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
#include "ui_ColorTemplatesDialog.h"
#include "ui_ColorTemplatesDialog.h"
#include <QtWidgets>
#include "settings.h"

class ColorTemplatesDialog : public QDialog
{
	Q_OBJECT

public:
	QString preferencesDirPath = "./Preferences";
	QString userTemplatesFileName = "UserTemplates.json";
	
	ColorTemplatesDialog(QWidget *parent = Q_NULLPTR);
	~ColorTemplatesDialog();

	ColorTemplate pickedTemplate, currentTemplate;
private:
	Ui::ColorTemplatesDialog ui;

	std::vector<NamedColorTemplate*> templates;

	int selectedRow = 0;
	long long maxTemplateID = 0;

	void readTemplatesFromFile(QString filename, std::vector<NamedColorTemplate*> & templates);
	void insertNewColorRow(int numOfRow, NamedColorTemplate namedTemplate);
	void writeTemplatesToFile(QString filename, std::vector<NamedColorTemplate*> templates);
	

private slots:
	void tableItemDoubleClicked(int row, int column);
	void tableItemClicked(int row, int column);
	void deleteColorTemplate();
	void saveCurrentTemplate();
	void templateNameEdited();
};
