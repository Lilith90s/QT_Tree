#include "MyLayoutItem.h"



MyLayoutItem::MyLayoutItem()
{
	zoom = new ZoomButton(20,20);
	setGraphicsItem(zoom);
}


MyLayoutItem::~MyLayoutItem()
{
}

QSizeF MyLayoutItem::sizeHint(Qt::SizeHint which, const QSizeF & constraint) const
{
	return QSizeF(20,20);
}
