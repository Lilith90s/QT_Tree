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
	Q_INTERFACES(QGraphicsItem)
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
	

	/*访问私有数据*/
	QString getText(){ return m_text; }
	MyItem* getFather(){ return this->father; }
	ZoomButton* getZoomButtom(){ return this->zoombuttom; }
	Curve* getCurve(){ return this->curve; }
	MyItem* getChild (int index);
	
	const int getChildNum() const { return this->childs.size(); }
	void setText(QString text) { this->m_text = text; }
	void setFather(MyItem* father) { this->father = father; }
	void removeChild(MyItem* item) {};
	void addChild(MyItem* item);
	
	void setItemMoveAble(bool flag) { }
	void setLevel(int level) { this->level = level; }
	void setHeightRange(QPoint range) { this->h_range = range; }
	void setXPos(int x) { this->x_pos = x; }
	int getLevel() { return level; }
	QPoint getHeightRange() { return this->h_range; }
	int  getXPos() { return x_pos; }
protected:
	QRectF boundingRect() const;
	QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	//void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
	void drawLigature();
	int type() const { return itemtype; };

private:
	QString m_text;
	MyItem* father;
	QList<MyItem*> childs;
	Curve* curve;
	ZoomButton* zoombuttom;
	// static QMenu menu;

	int x_pos;
	QPoint h_range;
	int level;
};

