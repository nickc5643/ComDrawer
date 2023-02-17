/********************************************************************************
** Form generated from reading UI file 'ComDrawer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMDRAWER_H
#define UI_COMDRAWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComDrawerClass
{
public:

    void setupUi(QWidget *ComDrawerClass)
    {
        if (ComDrawerClass->objectName().isEmpty())
            ComDrawerClass->setObjectName(QString::fromUtf8("ComDrawerClass"));
        ComDrawerClass->resize(938, 574);

        retranslateUi(ComDrawerClass);

        QMetaObject::connectSlotsByName(ComDrawerClass);
    } // setupUi

    void retranslateUi(QWidget *ComDrawerClass)
    {
        ComDrawerClass->setWindowTitle(QCoreApplication::translate("ComDrawerClass", "ComDrawer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ComDrawerClass: public Ui_ComDrawerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMDRAWER_H
