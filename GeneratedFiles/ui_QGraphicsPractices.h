/********************************************************************************
** Form generated from reading UI file 'QGraphicsPractices.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGRAPHICSPRACTICES_H
#define UI_QGRAPHICSPRACTICES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QGraphicsPracticesClass
{
public:

    void setupUi(QWidget *QGraphicsPracticesClass)
    {
        if (QGraphicsPracticesClass->objectName().isEmpty())
            QGraphicsPracticesClass->setObjectName(QStringLiteral("QGraphicsPracticesClass"));
        QGraphicsPracticesClass->resize(600, 400);

        retranslateUi(QGraphicsPracticesClass);

        QMetaObject::connectSlotsByName(QGraphicsPracticesClass);
    } // setupUi

    void retranslateUi(QWidget *QGraphicsPracticesClass)
    {
        QGraphicsPracticesClass->setWindowTitle(QApplication::translate("QGraphicsPracticesClass", "QGraphicsPractices", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QGraphicsPracticesClass: public Ui_QGraphicsPracticesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGRAPHICSPRACTICES_H
