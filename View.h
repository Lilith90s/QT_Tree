#pragma once
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qpushbutton.h>
#include <qvector.h>
#include "MyItem.h"
#include "MyScene.h"
#include <QWidget>


class View :
	public QGraphicsView
{
public:
	View(QWidget *parent = nullptr);
	~View();

protected:
	void resizeEvent(QResizeEvent* event);
private:
	MyScene* scene;
	Curve* curve;
	Data test_data;
};

