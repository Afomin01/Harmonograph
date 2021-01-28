#include "ColorTemplatesDialog.h"

ColorTemplatesDialog::ColorTemplatesDialog(QWidget* parent) : QDialog(parent) {
	ui.setupUi(this);

	QString expression = "[A-Za-z0-9 ]{0,20}";
	QRegularExpression rx(expression);
	QValidator* validator = new QRegularExpressionValidator(rx, this);

	ui.templateInputLine->setValidator(validator);

	QDir prefDir(preferencesDirPath);

	QFileInfoList fileInfoList = prefDir.entryInfoList(QStringList() << "*.json", QDir::Files);
	for (QFileInfo fileInfo : fileInfoList) {
		qInfo() << fileInfo.absoluteFilePath();
		readTemplatesFromFile(fileInfo.absoluteFilePath(), templates);
	}

	for (int i = 0; i < templates.size(); i++) {
		ColorTemplate currentTemplate = *templates.at(i);
		
		insertNewColorRow(i, currentTemplate);
	}

	
	connect(ui.colorsTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(tableItemDoubleClicked(int, int)));
	connect(ui.colorsTable, SIGNAL(cellClicked(int, int)), this, SLOT(tableItemClicked(int, int)));
	connect(ui.saveCureentTemplateBtn, SIGNAL(clicked()), this, SLOT(saveCurrentTemplate()));
	connect(ui.deleteTemplateBtn, SIGNAL(clicked()), this, SLOT(deleteColorTemplate()));
	connect(ui.templateInputLine, SIGNAL(textEdited(QString)), this, SLOT(templateNameEdited())); 
}

ColorTemplatesDialog::~ColorTemplatesDialog() {
}

void ColorTemplatesDialog::readTemplatesFromFile(QString filename, std::vector<ColorTemplate*> & templates) {
	QFile jsonFile(filename);

	try {
		jsonFile.open(QIODevice::ReadOnly);

		QByteArray saveData = jsonFile.readAll();

		QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));

		QJsonObject root = jsonDocument.object();

		QJsonArray preferences = root.value("preferences").toArray();

		for (int i = 0; i < preferences.size(); i++) {
			QJsonObject object = preferences.at(i).toObject();

			QString name = object.value("name").toString();

			QColor primary, secondary, background;
			primary.setNamedColor(object.value("primary").toString());
			secondary.setNamedColor(object.value("secondary").toString());
			background.setNamedColor(object.value("background").toString());

			templates.push_back(new ColorTemplate(name, primary, secondary, background));
		}
	}
	catch (...) {
	}

	jsonFile.close();
}

void ColorTemplatesDialog::insertNewColorRow(int numOfRow, ColorTemplate temp) {
	ui.colorsTable->insertRow(numOfRow);
	ui.colorsTable->setItem(numOfRow, 0, new QTableWidgetItem);
	ui.colorsTable->setItem(numOfRow, 1, new QTableWidgetItem);
	ui.colorsTable->setItem(numOfRow, 2, new QTableWidgetItem);
	ui.colorsTable->setItem(numOfRow, 3, new QTableWidgetItem);

	ui.colorsTable->item(numOfRow, 0)->setText(temp.name);
	ui.colorsTable->item(numOfRow, 1)->setBackground(temp.primaryColor);
	ui.colorsTable->item(numOfRow, 2)->setBackground(temp.secondaryColor);
	ui.colorsTable->item(numOfRow, 3)->setBackground(temp.backgroundColor);
}

void ColorTemplatesDialog::tableItemDoubleClicked(int row, int column) {
	ColorTemplate temp;
	temp.name = static_cast<QTableWidgetItem*>(ui.colorsTable->item(row, 0))->text();
	temp.primaryColor = static_cast<QTableWidgetItem*>(ui.colorsTable->item(row, 1))->background().color();
	temp.secondaryColor = static_cast<QTableWidgetItem*>(ui.colorsTable->item(row, 2))->background().color();
	temp.backgroundColor = static_cast<QTableWidgetItem*>(ui.colorsTable->item(row, 3))->background().color();

	pickedTemplate = temp;
	emit accept();
}

void ColorTemplatesDialog::tableItemClicked(int row, int column) {
	ui.deleteTemplateBtn->setEnabled(true);
}

void ColorTemplatesDialog::deleteColorTemplate() {
	qInfo() << ui.colorsTable->selectedItems().at(0)->text();
}

void ColorTemplatesDialog::saveCurrentTemplate() {
	QString name = ui.templateInputLine->text();

	if(name.length()>1) {
		QFileInfo info(QDir(preferencesDirPath), userTemplatesFileName);

		QFile userTemplatesFile(info.absoluteFilePath());
		
		try {
			userTemplatesFile.open(QIODevice::ReadWrite);

			std::vector<ColorTemplate*> userTemplates;
			readTemplatesFromFile(info.absoluteFilePath(), userTemplates);

			currentTemplate.name = name;
			userTemplates.push_back(&currentTemplate);

			QJsonDocument* document = new QJsonDocument();
			QJsonObject* root = new QJsonObject();
			QJsonArray* array = new QJsonArray();

			for (int i = 0; i < userTemplates.size(); i++) {
				ColorTemplate current = *userTemplates.at(i);
				QJsonObject temp;
				
				temp.insert("name", current.name);
				temp.insert("primary", current.primaryColor.name());
				temp.insert("secondary", current.secondaryColor.name());
				temp.insert("background", current.backgroundColor.name());

				array->insert(i, temp);
			}

			root->insert("preferences", *array);
			document->setObject(*root);
			
			userTemplatesFile.write(QJsonDocument(*document).toJson(QJsonDocument::Indented));

			userTemplates.clear();

			templates.push_back(new ColorTemplate(currentTemplate.name, currentTemplate.primaryColor, currentTemplate.secondaryColor, currentTemplate.backgroundColor));
			insertNewColorRow(ui.colorsTable->rowCount() - 1, currentTemplate);
			
			delete document;
			delete root;
			delete array;
			
		}catch (...) {
			
		}

		userTemplatesFile.close();
	}
}

void ColorTemplatesDialog::templateNameEdited() {
	ui.saveCureentTemplateBtn->setEnabled(ui.templateInputLine->text().length() > 1);
}
