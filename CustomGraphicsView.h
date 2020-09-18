#pragma once
#include <QGraphicsView>
#include <QWidget>
#include <QWheelEvent>

class CustomGraphicsView : public QGraphicsView {
	Q_OBJECT

public:
	CustomGraphicsView(QWidget* parent = nullptr) {
	}
protected:
	virtual void wheelEvent(QWheelEvent* event);

private: 

signals:
	void zoomChanged(int value);
};

