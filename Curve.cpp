#include "Curve.h"

Curve::Curve(QGraphicsItem * parent)
	:QGraphicsItem(parent)
{
	//points << pos1 << pos2 << pos3;
}

void Curve::drawCurve(QPointF pos1,QPointF pos3)
{
	points.clear();
	points << pos1 << pos3;
	update();
}

Curve::~Curve()
{

}


QRectF Curve::boundingRect() const
{
	return QRectF(0,0,0,0);
}

void Curve::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (points.size() == 0)
	{
		return;
	}
	QPainterPath path(points[0]);
	//计算
	for (int i = 0; i < points.size() - 1; ++i) {
		// 控制点的 x 坐标为 sp 与 ep 的 x 坐标和的一半
		// 第一个控制点 c1 的 y 坐标为起始点 sp 的 y 坐标
		// 第二个控制点 c2 的 y 坐标为结束点 ep 的 y 坐标
		QPointF sp = points[i];
		QPointF ep = points[i + 1];
		QPointF c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
		QPointF c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
		path.cubicTo(c1, c2, ep);
	}
	//设置渲染提示为消除锯齿
	painter->setRenderHint(QPainter::Antialiasing, true);
	//设置画笔颜色和宽度
	painter->setPen(QPen(Qt::black, 2));
	//将坐标系转换为矢量
	//painter->translate(40, 130);
	//绘制path
	painter->drawPath(path);
	// 绘制曲线上的点
	//painter->setBrush(Qt::gray);
	////绘制曲线上的点
	for (int i = 0; i < points.size(); ++i) {
		painter->drawEllipse(points[i], 2, 2);
	}

	QPen pen;
	pen.setColor(Qt::red);
	//pen.setBrush(QBrush(QColor(Qt::green)));
	painter->setPen(pen);
	painter->drawRect(boundingRect());
}
