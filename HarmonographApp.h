#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HarmonographApp.h"

class HarmonographApp : public QMainWindow
{
    Q_OBJECT

public:
    HarmonographApp(QWidget *parent = Q_NULLPTR);

private:
    Ui::HarmonographAppClass ui;
};
