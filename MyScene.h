#include <qgraphicsscene.h>
#include <MyItem.h>
#include <Curve.h>
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
public:	
	MyScene(Data* data,int view_width,int view_height,QGraphicsScene *parent = 0);
	~MyScene();
	MyItem *init(Data* data,MyItem* father);
	void add_MyItems(MyItem* item, int last_width, int last_height,int level,int space,int i);
protected:
	//void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
	MyItem *item;
	int imax_level;
	// 测试数据
	int view_width;
	int view_height;
};

