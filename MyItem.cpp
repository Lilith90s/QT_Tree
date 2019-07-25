#include "MyItem.h"



MyItem::MyItem( QString text, MyItem* father,  QGraphicsItem *parent) :
	QGraphicsItem(parent)
{
	curve = new Curve();
	this->father = father;
	if (father != nullptr)
	{
		this->father = father;
		father->childs.append(this);
	}
	qDebug() << "created myitem text: " << text;
	//zoombuttom = nullptr;
	zoombuttom = nullptr;
	if (childs.size() == 0)
	{
		zoombuttom = new ZoomButton(zoombuttom_width, zoombutton_height);
	}
	
	childs.clear();
	m_text = text;
	setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	// setFlags(QGraphicsItem::mov)
	this->setAcceptedMouseButtons(Qt::LeftButton);
	
	drawLigature();

}


MyItem::~MyItem()
{
	m_text = "";
	
	childs.clear();
	if (father != nullptr)
	{
		father = nullptr;
	}
	if (curve != nullptr)
	{
		delete curve;
		curve = nullptr;
	}
	if (zoombuttom != nullptr)
	{
		delete zoombuttom;
		zoombuttom = nullptr;
	}
}


QRectF MyItem::boundingRect() const
{
	return QRectF(0,0,m_iwidth,m_iheight);
}

QSizeF MyItem::sizeHint(Qt::SizeHint which, const QSizeF & constraint) const
{
	return QSizeF(m_iwidth,m_iheight);
}

void MyItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->drawRect(0, 0, m_iwidth, m_iheight);
	painter->drawText(0, 0, m_iwidth, m_iheight , Qt::AlignCenter, m_text);
	QPen pen;
	pen.setColor(Qt::red);
	//pen.setBrush(QBrush(QColor(Qt::green)));
	painter->setPen(pen);
	painter->drawRect(boundingRect());
	
}


void MyItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{	
	
	if (father != nullptr && zoombuttom != nullptr)
	{
		QGraphicsItem::mouseMoveEvent(event);
		zoombuttom->setPos(pos().rx() + m_iwidth, pos().ry());
	}
	drawLigature();
	//qDebug() << m_text << " moved to " << pos();
}

//void MyItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
//{
//	//setCursor(Qt::IBeamCursor);
//}


void MyItem::setPos(qreal ax, qreal ay)
{
	QGraphicsItem::setPos(ax, ay);
	if (zoombuttom != nullptr)
	{
		zoombuttom->setPos(ax + m_iwidth, ay);
	}
	drawLigature();
}

void MyItem::drawLigature()
{
	//qDebug() << "draw" << endl;
	int zoom_x = 0;
	if (zoombuttom != nullptr)
	{
		zoom_x = zoombuttom->m_width;
	}
	if (father != nullptr)
	{
		//qDebug() << father->m_text << " to " << m_text;
		auto pos1 = father->pos();
		pos1 = QPoint(pos1.rx() + MyItem::m_iwidth +zoom_x, pos1.ry() + MyItem::m_iheight / 2);
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
		pos1 = QPoint(pos1.rx() + MyItem::m_iwidth + zoom_x, pos1.ry() + MyItem::m_iheight / 2);
		auto pos3 = childs[i]->pos();
		pos3 = QPoint(pos3.rx(), pos3.ry() + MyItem::m_iheight / 2);
		childs[i]->curve->drawCurve(pos1, pos3);
	}
}


/**********************slots*******************************/

// 隐藏子节点
void MyItem::hideOrShowChilds(MyItem* item)
{
	if (NULL == item)
	{
		return;
	}

	if (item->childs.size() == 0)
	{
		return;
	}

	for (size_t i = 0; i < item->childs.size(); i++)
	{
		hideOrShowChilds(item->childs[i]);
		item->childs[i]->setVisible(!item->childs[i]->isVisible());
		item->childs[i]->curve->setVisible(!item->childs[i]->curve->isVisible());
		if (item->childs[i]->zoombuttom != nullptr)
		{
			item->childs[i]->zoombuttom->setVisible(!item->childs[i]->zoombuttom->isVisible());
		}
	}
}

MyItem* MyItem::getChild(int index)
{
	if (childs.size()>index)
	{
		return childs[index];
	}
	return nullptr;
}

void MyItem::addChild(MyItem * child)
{
	childs.append(child);
	if (child->father != nullptr)
	{
		child->level = child->father->level + 1;
	}
	else
	{
		child->level = 0;
	}
	

	qDebug() << m_text << "add layout from " << child->m_text;
}

