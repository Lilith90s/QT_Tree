#include "MyScene.h"
#include <qpushbutton.h>

MyScene::MyScene(Data* data, int view_width, int view_height, QGraphicsScene *parent)
	: QGraphicsScene(parent),view_width(view_width),view_height(view_height)
{
	//qDebug() << width() << height();
	lineedit = new QLineEdit();

	item = init(data,nullptr);
	setItemsPos(item,0,view_height/2,0);
	
	//QGraphicsWidget *pushButton = addWidget(new QPushButton);
	//main_layout->addItem(pushButton);
	
	lineedit->setContextMenuPolicy(Qt::NoContextMenu);
	lineedit_proxy = addWidget(lineedit);
	lineedit_proxy->hide();
	editing_item = nullptr;
	lineedit_proxy->setZValue(1);
	QObject::connect(lineedit, SIGNAL(editingFinished()), this, SLOT(changeItemText()));
	// QObject::connect(lineedit, SIGNAL(focusOutEvent()), this, SLOT(changeItemText()));
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
		// qDebug() << father->m_text << " << " << nowNode->m_text;
		father->addChild(nowNode);
		// qDebug() << father->childs.size();
		nowNode->setFather(father);
		// nowNode->father = father;
	}
	addItem(nowNode);
	addItem(nowNode->getCurve());
	/* 添加缩放按钮 */
	if (nowNode->getChildNum() > 0)
	{
		if (nowNode->getZoomButtom() /*nowNode->zoombuttom*/ != nullptr)
		{
			addItem(nowNode->getZoomButtom());
		}
	}
	return nowNode;
}
// 尾序遍历树，并添加到场景中
void MyScene::setItemsPos(MyItem * item,int start_h,int end_h,int level /*记录层级*/)
{
	/********************* 使用点阵方式对齐 ***********************/
	level++;
	for (size_t i = 0; i < item->getChildNum(); i++)
	{
		setItemsPos(item->getChild(i),
				(end_h-start_h)/item->getChildNum()*i + start_h, (end_h - start_h) / item->getChildNum()*(i+1)+start_h,
				level);
	}
	if (level>imax_level)
	{
		imax_level = level;
	}
	// qDebug() << level;
	int brother_size;
	if (item->getFather() != nullptr)
	{
		brother_size = item->getFather()->getChildNum();
	}
	else
	{
		brother_size = 2;
	}
	// x：层级乘以每个item占宽
	// y：起始位置加上兄弟节点之间的占位
	item->setPos((level-1)*150, (end_h - start_h) / brother_size + start_h);
	item->setHeightRange(QPoint(start_h, end_h));
	item->setLevel(level);
	item->setXPos((level - 1)*150);
	// item->x_pos = view_width / imax_level * level - 200;
	/********************* 使用点阵方式对齐 ***********************/
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	QTransform trasfrom;
	if (event->button() == Qt::LeftButton)
	{
		
		QPoint real_pos(event->scenePos().rx() - 80, event->scenePos().ry());
		// 获取当前点击位置的item
		ZoomButton* iszoom = nullptr;
		auto clickitem = itemAt(event->scenePos(), trasfrom);
		//iszoom = reinterpret_cast<ZoomButton*>(itemAt(event->scenePos(), trasfrom));
		qDebug() << event->scenePos();
		if (clickitem != nullptr && clickitem->type() == ItemType::ZOOMBUTTON)
		{
			//qDebug() << iszoom->objectName();
			// 点击的缩放按钮左边的矩形框
			MyItem* clickmyitem = nullptr;
			clickmyitem = reinterpret_cast<MyItem*>(itemAt(real_pos, trasfrom));
			// 判断是否初始化
			// if (clickmyitem != nullptr && clickmyitem->m_text == "")
			// {
			// 	return;
			// }
			if (clickmyitem != nullptr)
			{
				// qDebug() << clickmyitem->zValue();
				clickmyitem->hideOrShowChilds(clickmyitem);
				clickmyitem->getZoomButtom()->changeStatus();
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
		if (clickitem != nullptr&&clickitem->type() == ItemType::MYITEM)
		{
			auto item = qgraphicsitem_cast<MyItem*>(clickitem);
			auto newitem = new MyItem("newItem");
			addNewItem(item, newitem);
			qDebug() << "created " << newitem->getText() << "from " << newitem->getFather()->getText();
			for (size_t i = 0; i < newitem->getFather()->getChildNum(); i++)
			{
				qDebug() << newitem->getFather()->getChild(i)->getText();
			}
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
				editing_item->setText(lineedit->text());
				lineedit->setText("");
			}

			editing_item = qgraphicsitem_cast<MyItem*>(item);
			lineedit_proxy->show();
			lineedit_proxy->setPos(item->pos());
			lineedit->resize(editing_item->m_iwidth + 1, editing_item->m_iheight + 1);
			lineedit->setFocus();
			qDebug() << "now editing " << editing_item->getText();
		}
	}
	else
	{
		QGraphicsScene::mouseDoubleClickEvent(event);
	}

}

void MyScene::addNewItem(MyItem * item, MyItem* newitem)
{
	/********************* 使用点阵方式对齐添加 ***********************/
	addItem(newitem);
	addItem(newitem->getCurve());
	if (item->getChildNum() == 0)
	{
		addItem(item->getZoomButtom());
	}
	//addItem(newitem->zoombuttom);
	item->addChild(newitem);

	newitem->setFather(item);
	// newitem->level = item->level + 1;
	if (item->getLevel()>= imax_level)
	{
		imax_level++;
	}
	int total_space = item->getHeightRange().ry() - item->getHeightRange().rx();
	int space = total_space / item->getChildNum();
	for (size_t i = 0; i < item->getChildNum(); i++)
	{
		setItemsPos(item->getChild(i), total_space / item->getChildNum()*i + item->getHeightRange().rx(),
			total_space / item->getChildNum()*(i + 1) + item->getHeightRange().rx(),
			item->getLevel());
		//item->childs[i]->setPos(item->x_pos+view_width/imax_level, space*(i)+item->start_height);
	}
	lineedit_proxy->stackBefore(newitem);
	update();
	/********************* 使用点阵方式对齐 ***********************/
	
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
			editing_item->setText(lineedit->text());
		}
		lineedit_proxy->hide();
		editing_item = nullptr;
		lineedit->setText("");
	}
}