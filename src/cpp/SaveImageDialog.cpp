#include "SaveImageDialog.h"

SaveImageDialog::SaveImageDialog(QWidget *parent): QDialog(parent){
	ui.setupUi(this);
	saveWidth = 1920;
	saveHeight = 1080;
}

SaveImageDialog::~SaveImageDialog(){
	
}


void SaveImageDialog::accept() {
	useSquareImage = ui.useSquareImageCheckBox->checkState() == 2;

	QString str;
	if (useSquareImage) str = ui.squareResComboBox->currentText();
	else str = ui.regularResComboBox->currentText();

	saveWidth = str.split("x").at(0).toInt();
	saveHeight = str.split("x").at(1).toInt();

	useAntialiasing = ui.useAntialiasingCheckBox->checkState() == 2;

	transpBack = ui.transpBackCheckBox->checkState() == 2;

	penWidth = ui.penWidthSpinBox->value();

	borderPercentage = ui.borderPercentageSpinBox->value();

	QDialog::accept();
}