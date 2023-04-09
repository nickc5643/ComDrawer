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
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <fstream>



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
    void createComicBook();
    void openComicBook();
    QString getActiveComicBook();
    std::string getActiveComicBookConfigurationFile();

protected:

private slots:
    
    void addPage();
    void removePage();
    void pageSelect();
    void downloadComicBook();

private:
    void createActions();
    void createMenus();
    void readTextFile(std::string comicTitle);
    void uploadImage(int panel, std::string filename, QGridLayout* page);
    void setPageNumber(int newPage);

    QAction* pagesAct;
    QAction* addPageAct;
    QAction* removePageAct;
    QAction* downloadComicAct;
    QMenu* fileMenu;
    Ui::ComicBook ui;
    QWidget* comicBookArea;
    int maxPages = 37;
    int defaultPages = 5;
    int currentPage = 0;
    int coverPage = 0;
    int pageCount = 5;
    int maxPanelCount;
    int backPage = 4;
    QString _activeComicBook;
    std::string _activeComicBookConfigurationFile;
};

