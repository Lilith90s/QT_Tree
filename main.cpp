#include "QGraphicsPractices.h"
#include <QtWidgets/QApplication>
#include "View.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	View view;
	view.show();
	return a.exec();
}
