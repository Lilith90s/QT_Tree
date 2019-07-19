#include "MyScene.h"

MyScene::MyScene(Data* data, int view_width, int view_height, QGraphicsScene *parent)
	: QGraphicsScene(parent),view_width(view_width),view_height(view_height)
{
	//qDebug() << width() << height();
	item = init(data,nullptr);
	auto p = item;
	add_MyItems(item,0,view_height/2,0,0,0);
}

MyScene::~MyScene()
{
}

MyItem * MyScene::init(Data* data, MyItem* father)
{
	// 创建当前节点数据指针
	MyItem* nowNode = new MyItem(data->m_text);
	for (size_t i = 0; i < data->childs.size(); i++)
	{	
		init(data->childs[i],nowNode);
	}
	if (father != nullptr)
	{
		//qDebug() << father->m_text << " << " << nowNode->m_text;
		father->childs.append(nowNode);
		nowNode->father = father;
	}
	else
	{
		//qDebug() << "root Node : " << nowNode->m_text;
	}

	return nowNode;
}
// 尾序遍历树，并添加到场景中
void MyScene::add_MyItems(MyItem * item,int start_h,int end_h,int level /*记录层级*/,int space /*记录纵向位置*/,int i)
{
	level++;
	for (size_t i = 0; i < item->childs.size(); i++)
	{
			add_MyItems(item->childs[i],
				(end_h-start_h)/item->childs.size()*i + start_h, (end_h - start_h) / item->childs.size()*(i+1)+start_h,
				level, (end_h - start_h) / item->childs.size(), i);
	}
	if (level>imax_level)
	{
		imax_level = level;
	}
	// qDebug() << level;
	addItem(item);
	addItem(item->curve);
	// qDebug() << item->m_text << " from " << start_h << " to " << end_h;
	item->setPos(view_width / imax_level * level - 200, end_h-start_h/2 + start_h);	
}

//void MyScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
//{
//	//qDebug() << event->scenePos();
//
//	QGraphicsScene::mousePressEvent(event);
//}
//
void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	//qDebug() << event->scenePos();
	//QTransform transfrom;
	//auto item = reinterpret_cast<MyItem*>(itemAt(event->scenePos(), transfrom));
	//if (item != NULL)
	//{
	//	qDebug() << item->m_text;
	//}
	QGraphicsScene::mouseMoveEvent(event);
	update();
}

void MyScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
	//QGraphicsScene::mouseDoubleClickEvent(event);
	QTransform transfrom;
	auto item = reinterpret_cast<MyItem*>(itemAt(event->scenePos(), transfrom));
	qDebug() << "mouse double clicked";
	if (item != NULL)
	{
		item->hideOrShowChilds(item);
		update();
	}
}

//void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
//{
//	QGraphicsScene::mousePressEvent(event);
//}

