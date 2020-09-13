#pragma once

#include <Qwidget>
#include <QFileDialog>

class ImageSaver {
public:
	ImageSaver();
	void saveImage(QString filename, QImage image);
	int getSaveWidth() {
		return saveImageWidth;
	}
	int getSaveHeight() {
		return saveImageHeight;
	}
	
private:
	int saveImageWidth = 2560;
	int saveImageHeight = 1440;
};

