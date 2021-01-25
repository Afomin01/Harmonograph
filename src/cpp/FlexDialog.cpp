#include "FlexDialog.h"

FlexDialog::FlexDialog(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);
	useAntiAliasing = ui.antialiasingCheckBox->isChecked();
	FPS = ui.FPSSpinBox->value();
}

FlexDialog::~FlexDialog(){
}

void FlexDialog::changeBase(int value) {
	if(value==0){
		flexBaseMode = FlexModes::phaseBased;
	}
	else if(value==1){
		flexBaseMode = FlexModes::frequencyBased;
	}
}

void FlexDialog::useAntialiasingState(int state) {
	useAntiAliasing = state == 2;
}

void FlexDialog::setFPS(int value) {
	FPS = value;
}