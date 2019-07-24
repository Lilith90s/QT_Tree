#include <qgraphicsscene.h>
#include <QGraphicsProxyWidget>
#include <MyItem.h>
#include <Curve.h>
#include "ZoomButton.h"
struct Data
{
	Data() {};
	Data(QString text) { m_text = text; };
	QString m_text;
	Data* father;
	QList<Data*> childs;
};
// 管理item
// 1.添加矩形
// 2.添加线段
class MyScene :
	public QGraphicsScene
{
	Q_OBJECT
public:	
	MyScene(Data* data,int view_width,int view_height,QGraphicsScene *parent = 0);
	~MyScene();
	MyItem *init(Data* data,MyItem* father);
	void setItemsPos(MyItem* item, int last_width, int last_height,int level);
public slots:
	void changeItemText();
	//void setEditingItem();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	
private:
	void addNewItem(MyItem* item, MyItem* newitem);

	MyItem *item;
	MyItem *editing_item;
	int imax_level;
	// 测试数据
	int view_width;
	int view_height;
	QGraphicsProxyWidget * lineedit_proxy;
	QLineEdit* lineedit;
};

