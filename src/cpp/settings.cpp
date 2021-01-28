#pragma once
#include "settings.h"

ColorTemplate::ColorTemplate(QString name, QColor primary, QColor secondary, QColor background) {
	this->name = name;
	primaryColor = primary;
	secondaryColor = secondary;
	backgroundColor = background;
}
