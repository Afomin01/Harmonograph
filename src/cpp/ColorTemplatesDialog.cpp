#include "ColorTemplatesDialog.h"

ColorTemplatesDialog::ColorTemplatesDialog(QWidget* parent) : QDialog(parent) {
	ui.setupUi(this);

	//ui.colorsTable->setColumnHidden(0, true);

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
		NamedColorTemplate currentTemplate = *templates.at(i);
		
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

void ColorTemplatesDialog::readTemplatesFromFile(QString filename, std::vector<NamedColorTemplate*> & templates) {
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

			NamedColorTemplate* namedTemplate = new NamedColorTemplate(maxTemplateID, QFileInfo(filename).fileName(), name, ColorTemplate(primary, secondary, background));

			templates.push_back(namedTemplate);
			maxTemplateID++;
		}
	}
	catch (...) {
	}

	jsonFile.close();
}

void ColorTemplatesDialog::insertNewColorRow(int numOfRow, NamedColorTemplate namedTemplate) {
	ui.colorsTable->insertRow(numOfRow);
	ui.colorsTable->setItem(numOfRow, 0, new QTableWidgetItem);
	ui.colorsTable->setItem(numOfRow, 1, new QTableWidgetItem);
	ui.colorsTable->setItem(numOfRow, 2, new QTableWidgetItem);
	ui.colorsTable->setItem(numOfRow, 3, new QTableWidgetItem);
	ui.colorsTable->setItem(numOfRow, 4, new QTableWidgetItem);

	ui.colorsTable->item(numOfRow, 0)->setText(QString::number(namedTemplate.id));
	ui.colorsTable->item(numOfRow, 1)->setText(namedTemplate.name);
	ui.colorsTable->item(numOfRow, 2)->setBackground(namedTemplate	.colorTemplate.primaryColor);
	ui.colorsTable->item(numOfRow, 3)->setBackground(namedTemplate.colorTemplate.secondaryColor);
	ui.colorsTable->item(numOfRow, 4)->setBackground(namedTemplate.colorTemplate.backgroundColor);
}

void ColorTemplatesDialog::writeTemplatesToFile(QString filename, std::vector<NamedColorTemplate*> templates) {
	QFile file(filename);

	QJsonDocument* document = new QJsonDocument();
	QJsonObject* root = new QJsonObject();
	QJsonArray* array = new QJsonArray();
	
	try {
		file.open(QIODevice::WriteOnly);

		for (int i = 0; i < templates.size(); i++) {
			NamedColorTemplate current = *templates.at(i);
			QJsonObject temp;

			temp.insert("name", current.name);
			temp.insert("primary", current.colorTemplate.primaryColor.name());
			temp.insert("secondary", current.colorTemplate.secondaryColor.name());
			temp.insert("background", current.colorTemplate.backgroundColor.name());

			array->insert(i, temp);
		}

		root->insert("preferences", *array);
		document->setObject(*root);

		file.write(QJsonDocument(*document).toJson(QJsonDocument::Indented));
	}catch (...){}

	file.close();

	delete document;
	delete root;
	delete array;
}

void ColorTemplatesDialog::tableItemDoubleClicked(int row, int column) {
	ColorTemplate temp;
	
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
	long long ID =  ui.colorsTable->selectedItems().at(0)->text().toLongLong();

	NamedColorTemplate* templateToDelete = nullptr;

	//needed to get filename
	for(auto t : templates) {
		if(t->id == ID) {
			templateToDelete = t;
		}
	}

	if (templateToDelete != nullptr) {
		QFileInfo info(QDir(preferencesDirPath), templateToDelete->filename);

		std::vector<NamedColorTemplate*> fileTemplates;

		for (auto t : templates) {
			if (t->filename == templateToDelete->filename && t->id != ID) {
				fileTemplates.push_back(t);
			}
		}

		writeTemplatesToFile(info.absoluteFilePath(), fileTemplates);

		auto it = templates.begin();
		while (it != templates.end()) {
			if ((*it)->id == ID) {
				templates.erase(it);
				break;
			}
		}

		ui.colorsTable->removeRow(ui.colorsTable->selectedRanges().at(0).topRow());
	}
}

void ColorTemplatesDialog::saveCurrentTemplate() {
	QString name = ui.templateInputLine->text();

	if (name.length() > 1) {
		QFileInfo info(QDir(preferencesDirPath), userTemplatesFileName);

		std::vector<NamedColorTemplate*> userTemplates;

		for (auto t : templates) {
			if (t->filename == userTemplatesFileName) {
				userTemplates.push_back(t);
			}
		}

		NamedColorTemplate* colorTemplateToSave = new NamedColorTemplate(maxTemplateID, info.absoluteFilePath(), name, currentTemplate);

		userTemplates.push_back(colorTemplateToSave);

		writeTemplatesToFile(info.absoluteFilePath(), userTemplates);

		userTemplates.clear();

		templates.push_back(colorTemplateToSave);
		maxTemplateID++;
		insertNewColorRow(ui.colorsTable->rowCount(), *colorTemplateToSave);

	}
}

void ColorTemplatesDialog::templateNameEdited() {
	ui.saveCureentTemplateBtn->setEnabled(ui.templateInputLine->text().length() > 1);
}
