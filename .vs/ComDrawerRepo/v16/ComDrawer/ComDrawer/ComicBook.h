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
#include <QGridLayout>

/*
* The purpose of this class is to control the main ComDrawer widget.
*/

class ComicBook : public QMainWindow
{
    Q_OBJECT

public:
    ComicBook(QWidget* parent = nullptr);
    ~ComicBook();
    int getPanelCount();
    void refresh();
    bool readFile();

protected:

private slots:
    
    void addPage();
    void removePage();
    void pageSelect();

private:
    void createActions();
    void createMenus();
    void readTextFile(const char& comic_title);
    void uploadImage(int panel, std::string filename);
    void setPageNumber(int newPage);

    QAction* refreshAct;
    QList<QAction*> pagesAct;
    QAction* addPageAct;
    QAction* removePageAct;
    QMenu* pageSelectMenu;
    Ui::ComicBook ui;
    QWidget* comicBookArea;
    int maxPages = 37;
    int defaultPages = 5;
    int currentPage = 0;
    int coverPage = 0;
    int pageCount = 5;
    int maxPanelCount;
    int backPage = 4;
    bool refreshPage;

};

