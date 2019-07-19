#pragma once

#include <QtWidgets/QWidget>
#include "ui_QGraphicsPractices.h"

class QGraphicsPractices : public QWidget
{
	Q_OBJECT

public:
	QGraphicsPractices(QWidget *parent = Q_NULLPTR);

private:
	Ui::QGraphicsPracticesClass ui;
};
