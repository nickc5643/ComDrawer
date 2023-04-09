/********************************************************************************
** Form generated from reading UI file 'ComicBook.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMICBOOK_H
#define UI_COMICBOOK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComicBook
{
public:
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ComicBook)
    {
        if (ComicBook->objectName().isEmpty())
            ComicBook->setObjectName(QString::fromUtf8("ComicBook"));
        ComicBook->resize(806, 605);
        centralwidget = new QWidget(ComicBook);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ComicBook->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ComicBook);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ComicBook->setStatusBar(statusbar);

        retranslateUi(ComicBook);

        QMetaObject::connectSlotsByName(ComicBook);
    } // setupUi

    void retranslateUi(QMainWindow *ComicBook)
    {
        ComicBook->setWindowTitle(QCoreApplication::translate("ComicBook", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ComicBook: public Ui_ComicBook {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMICBOOK_H
