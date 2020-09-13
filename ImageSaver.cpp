#include "ImageSaver.h"


ImageSaver::ImageSaver() {
	//load setting logic
}

void ImageSaver::saveImage(QString filename, QImage image) {
	image.save(filename);
}
