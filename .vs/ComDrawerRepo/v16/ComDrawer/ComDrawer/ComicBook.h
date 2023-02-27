#pragma once

#include <QtWidgets/QWidget>
#include "ui_ComicBook.h"
#include <QImage>
#include <QPoint>
#include <QColor>
#include <QMainWindow>
#include <QList>
#include <QAction>
#include "CanvasView.h"
#include <QLabel>
#include <String>
#include <QMessageBox>
#include <QMenuBar>
#include <QScrollArea>
#include <QColorDialog>
#include <QInputDialog>

/*
* The purpose of this class is to control the main ComDrawer widget.
*/

class ComicBook : public QMainWindow
{
    Q_OBJECT

public:
    ComicBook(QWidget* parent = nullptr);
    ~ComicBook();

protected:

private slots:
    void refresh();
    void addPage();
    void pageSelect();

private:
    void createActions();
    void createMenus();

    QAction* refreshAct;
    QList<QAction*> pagesAct;
    QAction* addPageAct;
    QMenu* pageSelectMenu;
    Ui::ComicBook ui;
    QWidget* comicBookArea;
    int maxPages = 37;
    int defaultPages = 5;

};

