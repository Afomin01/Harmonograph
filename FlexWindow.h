#pragma once

#include <QMainWindow>
#include "ui_FlexWindow.h"

class FlexWindow : public QMainWindow
{
	Q_OBJECT

public:
	FlexWindow(QWidget *parent = Q_NULLPTR);
	~FlexWindow();

private:
	Ui::FlexWindow ui;
};
