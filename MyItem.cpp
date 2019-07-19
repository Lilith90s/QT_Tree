#include "MyItem.h"



MyItem::MyItem(QString text, MyItem* father,  QGraphicsItem *parent) :
	QGraphicsItem(parent)
{
	this->father = father;
	if (father != nullptr)
	{
		this->father = father;
		father->childs.append(this);
	}

	m_text = text;
	setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	this->setAcceptedMouseButtons(Qt::LeftButton);
	curve = new Curve();
	drawLigature();
}


MyItem::~MyItem()
{
}


QRectF MyItem::boundingRect() const
{
	return QRectF(0,0,m_iwidth,m_iheight);
}

void MyItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->drawRect(0, 0, m_iwidth, m_iheight);
	painter->drawText(0, 0, m_iwidth, m_iheight , Qt::AlignCenter, m_text);
}


void MyItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{	
	QGraphicsItem::mouseMoveEvent(event);
	drawLigature();
	//qDebug() << m_text << " moved to " << pos();
}

void MyItem::setPos(qreal ax, qreal ay)
{
	QGraphicsItem::setPos(ax, ay);
	drawLigature();
}

void MyItem::drawLigature()
{
	//qDebug() << "draw" << endl;
	if (father != nullptr)
	{
		//qDebug() << father->m_text << " to " << m_text;
		auto pos1 = father->pos();
		pos1 = QPoint(pos1.rx() + MyItem::m_iwidth, pos1.ry() + MyItem::m_iheight / 2);
		auto pos3 = pos();
		auto x = abs((father->pos().rx() - pos().rx()) / 2);
		x = x + qMin(father->pos().rx(), pos().rx());
		auto y = abs((father->pos().ry() - pos().ry()) / 2);
		y = y + qMin(father->pos().ry(), pos().ry());
		auto pos2 = QPointF(x, y);
		pos3.setY(pos3.ry() + MyItem::m_iheight / 2);
		//qDebug() << pos1 << pos2 << pos3;
		curve->drawCurve(pos1, pos3);

	}
	for (size_t i = 0; i < childs.size(); i++)
	{
		auto pos1 = pos();
		pos1 = QPoint(pos1.rx() + MyItem::m_iwidth, pos1.ry() + MyItem::m_iheight / 2);
		auto pos3 = childs[i]->pos();
		pos3 = QPoint(pos3.rx(), pos3.ry() + MyItem::m_iheight / 2);
		childs[i]->curve->drawCurve(pos1, pos3);
	}
}


/**********************slots*******************************/

// 隐藏子节点
void MyItem::hideOrShowChilds(MyItem* item)
{
	for (size_t i = 0; i < item->childs.size(); i++)
	{
		hideOrShowChilds(item->childs[i]);
		item->childs[i]->setVisible(!item->childs[i]->isVisible());
		item->childs[i]->curve->setVisible(!item->childs[i]->curve->isVisible());
	}
}

