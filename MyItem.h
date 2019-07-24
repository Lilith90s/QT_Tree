#pragma once
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qpainter.h>
#include <qdebug.h>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include <string>
#include <qstring.h>
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qinputdialog.h>
#include <QTextItem>
#include <qmenu.h>
#include "Curve.h"
#include "ZoomButton.h"
#include "ItemType.h"


class MyItem :
	public QGraphicsItem
{
public:
	static const int m_iheight = 20;
	static const int m_iwidth = 80;
	static const int zoombuttom_width = 20;
	static const int zoombutton_height = 20;
	static const int itemtype = ItemType::MYITEM;
	MyItem(QString text = "",MyItem* father = nullptr, QGraphicsItem *parent = 0);
	void setPos(qreal ax, qreal ay);
	~MyItem();
	void hideOrShowChilds(MyItem* item);
protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	//void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
	void drawLigature();
	int type() const { return itemtype; };
private:

public:
	QString m_text;
	MyItem* father;
	QList<MyItem*> childs;
	Curve* curve;
	ZoomButton* zoombuttom;
	static QMenu menu;

	int x_pos;
	int start_height;
	int end_height;
	int level;
};

