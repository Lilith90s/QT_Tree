#include "QGraphicsPractices.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QGraphicsPractices w;
	w.show();
	return a.exec();
}
