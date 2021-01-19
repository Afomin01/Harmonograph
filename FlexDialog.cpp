#include "FlexDialog.h"

FlexDialog::FlexDialog(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);

}

FlexDialog::~FlexDialog(){
}

void FlexDialog::setBrush(int value) {
	penWidth = value;
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