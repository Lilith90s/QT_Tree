#pragma once
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qpushbutton.h>
#include <qvector.h>
#include "MyItem.h"
#include "MyScene.h"



class View :
	public QGraphicsView
{
public:
	View();
	~View();

protected:
	void resizeEvent(QResizeEvent* event);
private:
	MyScene* scene;
	Curve* curve;
	Data test_data;
};

