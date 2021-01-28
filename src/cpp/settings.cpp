#pragma once
#include "settings.h"

ColorTemplate::ColorTemplate(QColor primary, QColor secondary, QColor background) {
	primaryColor = primary;
	secondaryColor = secondary;
	backgroundColor = background;
}

NamedColorTemplate::NamedColorTemplate(long long id, QString filename, QString name, ColorTemplate colorTemplate) {
	this->id = id;
	this->filename = filename;
	this->name = name;
	this->colorTemplate = colorTemplate;
}
