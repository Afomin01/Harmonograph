#pragma once

#include <QGraphicsView>

class FlexGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	FlexGraphicsView(QWidget *parent);
	~FlexGraphicsView();
};
