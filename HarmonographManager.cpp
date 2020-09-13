#include "HarmonographManager.h"

HarmonographManager::HarmonographManager() {
    harmonograph = new Harmonograph(3);
    imagePainter = new ImagePainter();
    imageSaver = new ImageSaver();
}

QGraphicsPixmapItem* HarmonographManager::getRenderedGraphicsItem() {
    return new QGraphicsPixmapItem(QPixmap::fromImage(imagePainter->getImage(harmonograph)));
}

void HarmonographManager::updateRandomValues() {
    harmonograph->update();
}

void HarmonographManager::changeXAxisRotation(float radians) {
    harmonograph->rotateXAxis(radians);
}

void HarmonographManager::saveCurrentImage(QString filename) {
    imageSaver->saveImage(filename, imagePainter->getImageToSave(harmonograph, imageSaver->getSaveWidth(), imageSaver->getSaveHeight()));
}
