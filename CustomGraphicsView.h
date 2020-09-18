#pragma once
#include <QGraphicsView>
#include <QWidget>
#include <QWheelEvent>

class CustomGraphicsView : public QGraphicsView {
	Q_OBJECT

public:
	CustomGraphicsView(QWidget* parent = nullptr) {
		this->setCursor(Qt::OpenHandCursor);
	}
protected:
	virtual void wheelEvent(QWheelEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);

private: 
	bool isMousePressed = false;
	int previousX = 0;
	int previousY = 0;
	float stepPhaseX = 90;
	float stepPhaseY = 90;
	const float piTwo = (float)(2 * atan(1) * 4);

signals:
	void zoomChanged(int value);
	void rotateScene(float x, float y);
};

