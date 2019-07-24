#include "MyScene.h"

MyScene::MyScene(Data* data, int view_width, int view_height, QGraphicsScene *parent)
	: QGraphicsScene(parent),view_width(view_width),view_height(view_height)
{
	//qDebug() << width() << height();
	item = init(data,nullptr);
	setItemsPos(item,0,view_height/2,0);
	lineedit = new QLineEdit();
	lineedit->setContextMenuPolicy(Qt::NoContextMenu);
	lineedit_proxy = addWidget(lineedit);
	lineedit_proxy->hide();
	editing_item = nullptr;
	QObject::connect(lineedit, SIGNAL(editingFinished()), this, SLOT(changeItemText()));
	QObject::connect(lineedit, SIGNAL(focusOutEvent()), this, SLOT(changeItemText()));
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
		qDebug() << father->childs.size();
		nowNode->father = father;
	}
	else
	{
		//qDebug() << "root Node : " << nowNode->m_text;
	}
	addItem(nowNode);
	addItem(nowNode->curve);

	// qDebug() << nowNode->m_text << " from " << start_h << " to " << end_h;
	/* 添加缩放按钮 */
	if (nowNode->childs.size() > 0)
	{
		if (nowNode->zoombuttom != nullptr)
		{
			addItem(nowNode->zoombuttom);
		}
		//nowNode->zoombuttom->setPos(view_width / imax_level * level - 200 +nowNode->m_iwidth,
		//	end_h - start_h / 2 + start_h);
	}
	return nowNode;
}
// 尾序遍历树，并添加到场景中
void MyScene::setItemsPos(MyItem * item,int start_h,int end_h,int level /*记录层级*/)
{
	level++;
	for (size_t i = 0; i < item->childs.size(); i++)
	{
		setItemsPos(item->childs[i],
				(end_h-start_h)/item->childs.size()*i + start_h, (end_h - start_h) / item->childs.size()*(i+1)+start_h,
				level);
	}
	if (level>imax_level)
	{
		imax_level = level;
	}
	// qDebug() << level;
	int brother_size;
	if (item->father != nullptr)
	{
		brother_size = item->father->childs.size();
	}
	else
	{
		brother_size = 2;
	}
	item->setPos(view_width / imax_level * level - 200, end_h - start_h / brother_size + start_h);
	item->start_height = start_h;
	item->end_height = end_h;
	item->level = level;
	item->x_pos = view_width / imax_level * level - 200;
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	QTransform trasfrom;
	if (event->button() == Qt::LeftButton)
	{
		
		QPoint real_pos(event->scenePos().rx() - 80, event->scenePos().ry());
		// 获取当前点击位置的item
		ZoomButton* iszoom = nullptr;
		iszoom = reinterpret_cast<ZoomButton*>(itemAt(event->scenePos(), trasfrom));
		qDebug() << event->scenePos();
		if (iszoom != nullptr)
		{
			//qDebug() << iszoom->objectName();
			// 点击的缩放按钮左边的矩形框
			MyItem* clickitem = nullptr;
			clickitem = reinterpret_cast<MyItem*>(itemAt(real_pos, trasfrom));
			// 判断是否初始化
			if (clickitem != nullptr && clickitem->m_text == "")
			{
				return;
			}
			if (clickitem != nullptr)
			{
				clickitem->hideOrShowChilds(clickitem);
				clickitem->zoombuttom->changeStatus();
				update();
			}
		}	
		QGraphicsScene::mousePressEvent(event);
	}
	else if (event->button() == Qt::RightButton)
	{
		qDebug() << "right";
		auto clickPos = event->scenePos();
		auto clickitem = itemAt(clickPos, trasfrom);
		if (clickitem!=nullptr&&clickitem->type() == ItemType::MYITEM)
		{
			auto item = qgraphicsitem_cast<MyItem*>(clickitem);
			auto newitem = new MyItem("newItem",item);
			addNewItem(item, newitem);
			qDebug() << item->m_text;
		}
		QGraphicsScene::mousePressEvent(event);
	}

}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsScene::mouseMoveEvent(event);
	update();
}

void MyScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		//QGraphicsScene::mouseDoubleClickEvent(event);
		QTransform transfrom;
		auto item = (itemAt(event->scenePos(), transfrom));
		// 双击矩形框
		if (item != nullptr && item->type() == ItemType::MYITEM)
		{
			// 上一次编辑可能未结束
			if (editing_item != nullptr && lineedit->text() != "")
			{
				editing_item->m_text = lineedit->text();
				lineedit->setText("");
			}

			editing_item = qgraphicsitem_cast<MyItem*>(item);
			lineedit_proxy->show();
			lineedit_proxy->setPos(item->pos());
			lineedit->resize(editing_item->m_iwidth + 1, editing_item->m_iheight + 1);
			lineedit->setFocus();
			qDebug() << "now editing " << editing_item->m_text;
		}
	}
	else
	{
		QGraphicsScene::mouseDoubleClickEvent(event);
	}

}

void MyScene::addNewItem(MyItem * item, MyItem* newitem)
{
	addItem(newitem);
	addItem(newitem->curve);
	//addItem(newitem->zoombuttom);
	item->childs.append(newitem);
	newitem->level = item->level + 1;
	if (item->level == imax_level)
	{
		imax_level++;
	}
	int space = (item->end_height - item->start_height) / item->childs.size();;
	for (size_t i = 0; i < item->childs.size(); i++)
	{
		setItemsPos(item->childs[i], (item->end_height - item->start_height) / item->childs.size()*i + item->start_height,
			(item->end_height - item->start_height) / item->childs.size()*(i + 1) + item->start_height,
			item->level);
		//item->childs[i]->setPos(item->x_pos+view_width/imax_level, space*(i)+item->start_height);
	}
	
}

//void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
//{
//	qDebug() << "mouse release";
//	//QGraphicsScene::mousePressEvent(event);
//}

void MyScene::changeItemText()
{
	qDebug() << "finished editing!";
	if (editing_item != nullptr)
	{
		if (lineedit->text() != "")
		{
			editing_item->m_text = lineedit->text();
		}
		lineedit_proxy->hide();
		editing_item = nullptr;
		lineedit->setText("");
	}
}