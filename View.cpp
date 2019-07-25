#include "View.h"

View::View(QWidget *parent):QGraphicsView(parent)
{
	//resize(800, 600);
	//scene.addText("");
	//rectAngles = new RectAngles(squares);
	//scene = new MyScene();
	//squares = new MyItem("1");
	//scene->addItem(squares);
	//setScene(scene);
	//squares->setPos(width()/16, height()/2);
	//auto item = new MyItem("2",squares);
	//item->setPos(width() / 4, height() / 4);
	////rectAngles->addChild(new RectAngles(item));
	//scene->addItem(item);
	////curve = new Curve(squares->pos(),);
	//scene->addItem(item->curve);
	auto n1 = new Data("1");
	auto n2_1 = new Data("2-1");
	auto n2_2 = new Data("2-2");
	auto n3_1_1 = new Data("3-1-1");
	auto n3_1_2 = new Data("3-1-2");
	auto n3_2_1 = new Data("3-2-1");
	auto n3_2_2 = new Data("3-2-2");
	n1->childs.append(n2_1);
	n1->childs.append(n2_2);
	n2_1->childs.append(n3_1_1);
	n2_1->childs.append(n3_1_2);
	n2_2->childs.append(n3_2_1);
	n2_2->childs.append(n3_2_2);
	scene = new MyScene(n1,800, 600);
	setScene(scene);

}


View::~View()
{
}

void View::resizeEvent(QResizeEvent * event)
{
	setSceneRect(0, 0, width() - 2, height() - 2);
}
