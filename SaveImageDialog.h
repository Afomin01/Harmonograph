#pragma once

#include <QDialog>
#include "ui_SaveImageDialog.h"
#include "ui_SaveImageDialog.h"

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

private:
	Ui::SaveImageDialog ui;
private slots:
	virtual void accept();
};
