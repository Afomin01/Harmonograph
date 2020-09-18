#include "CustomGraphicsView.h"

void CustomGraphicsView::wheelEvent(QWheelEvent* event) {

	QPoint numDegrees = event->angleDelta() / 8;

	int yDegrees = numDegrees.y();

	emit zoomChanged(yDegrees);
}
