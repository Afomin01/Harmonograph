#include "CustomGraphicsView.h"

void CustomGraphicsView::wheelEvent(QWheelEvent* event) {

	QPoint numDegrees = event->angleDelta() / 8;

	int yDegrees = numDegrees.y();

	emit zoomChanged(yDegrees);
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent* event) {
	if (isMousePressed) {
		int dx = previousX - (int)event->globalX();
		int dy = previousY - (int)event->globalY();

		float dfX = ((dx / stepPhaseX) * piTwo);
		float dfY = ((dy / stepPhaseY) * piTwo);

		previousX = event->globalX();
		previousY = event->globalY();
		emit rotateScene(dfX, dfY);
	}
}

void CustomGraphicsView::mousePressEvent(QMouseEvent* event) {
	isMousePressed = true;
	previousX = event->globalX();
	previousY = event->globalY();
	this->setCursor(Qt::ClosedHandCursor);

}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent* event) {
	isMousePressed = false;
	this->setCursor(Qt::OpenHandCursor);
}

