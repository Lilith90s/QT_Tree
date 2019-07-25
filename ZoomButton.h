#pragma once
#include <qpainter.h>
#include <qgraphicslayoutitem.h>
#include <qgraphicsitem.h>
#include <ItemType.h>
class ZoomButton : 
	public QGraphicsItem
{
	Q_INTERFACES(QGraphicsItem)
public:
	
	const ItemType itemtype = ItemType::ZOOMBUTTON;
	ZoomButton(int width=10,int height=10, QGraphicsItem* father = 0);
	void changeStatus();
	~ZoomButton();
	int m_width;
	int m_height;

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	int type() const { return itemtype; };
private:
	bool isVisable;

};

