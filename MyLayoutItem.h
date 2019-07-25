#pragma once
#include <qgraphicslayoutitem.h>
#include "ZoomButton.h"
class MyLayoutItem :
	public QGraphicsLayoutItem
{
public:
	MyLayoutItem();
	~MyLayoutItem();
protected:
	QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;
private:
	ZoomButton* zoom;


};

