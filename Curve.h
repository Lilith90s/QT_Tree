#pragma once
#include <qgraphicsitem.h>
#include <qpainter.h>
#include <qlist.h>
#include <qgraphicsscene.h>
class Curve :
	public QGraphicsItem
{
public:
	Curve(QGraphicsItem *parent = 0);
	void drawCurve(QPointF pos1,QPointF pos3);
	~Curve();
public slots:
	static void drawCurve(QGraphicsItem* item1, QGraphicsItem* item2,QGraphicsScene* scene,Curve* curve);
protected:
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	QList<QPointF> points;
};

