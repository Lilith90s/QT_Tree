#include "ZoomButton.h"



ZoomButton::ZoomButton(int width, int height, QGraphicsItem* parent)
{
	this->m_width = width;
	this->m_height = height;
	isVisable = true;
}

void ZoomButton::changeStatus()
{
	
	isVisable = !isVisable;
	update();
}


ZoomButton::~ZoomButton()
{
}

QRectF ZoomButton::boundingRect() const
{
	return QRectF(0,0,m_width,m_height);
}


void ZoomButton::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->drawRect(0, 0, m_width, m_height);
	if (isVisable == true)
	{
		painter->drawText(0, 0, m_width, m_height, Qt::AlignCenter, "-");
	}else{
		painter->drawText(0, 0, m_width, m_height, Qt::AlignCenter, "+");
	}

}

