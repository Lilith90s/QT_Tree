#include "QGraphicsPractices.h"
#include <QtWidgets/QApplication>
#include <QTextEdit>
#include "View.h"
#include "MyLayoutItem.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QGraphicsPractices view;
	view.show();
	// QGraphicsScene scene;
	// QGraphicsWidget *textEdit = scene.addWidget(new QTextEdit);
	// QGraphicsWidget *pushButton = scene.addWidget(new QPushButton);
	// QGraphicsWidget *big = scene.addWidget(new QTextEdit);
	// 
	// QGraphicsLinearLayout *layout = new QGraphicsLinearLayout();
	// layout->setOrientation(Qt::Vertical);
	// layout->addItem(textEdit);
	// layout->addItem(pushButton);
	// QGraphicsLinearLayout *self = new QGraphicsLinearLayout();
	// self->addItem(big);
	// self->addItem(layout);
	// MyLayoutItem* test = new MyLayoutItem();
	// //self->addItem(test);
	// layout->addItem(test);
	// //scene.addItem(test1);
	// qDebug() << self->count();
	// //self->insertItem(1, test);
	// //self->insertStretch(0, 1);
	// self->setSpacing(40);
	// QGraphicsWidget *form = new QGraphicsWidget;
	// form->setLayout(self);
	// scene.addItem(form);
	// QGraphicsView view;
	// view.setScene(&scene);
	// view.show();
	return a.exec();
}
