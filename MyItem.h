#pragma once
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qpainter.h>
#include <qdebug.h>
#include <QGraphicsSceneMouseEvent>
#include <qstring.h>
#include "Curve.h"
class MyItem :
	public QGraphicsItem
{
public:
	static const int m_iheight = 20;
	static const int m_iwidth = 80;
	MyItem(QString text = "",MyItem* father = nullptr, QGraphicsItem *parent = 0);
	void setPos(qreal ax, qreal ay);
	~MyItem();
public slots:
	void hideOrShowChilds(MyItem* item);
protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	
	void drawLigature();
public:
	QString m_text;
	MyItem* father;
	QList<MyItem*> childs;
	Curve* curve;
};

