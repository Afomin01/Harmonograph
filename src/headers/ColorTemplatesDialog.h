#pragma once

#include <QDialog>
#include "ui_ColorTemplatesDialog.h"
#include "ui_ColorTemplatesDialog.h"
#include "json.hpp"
#include <QtWidgets>
#include "settings.h"

using json = nlohmann::json;

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
