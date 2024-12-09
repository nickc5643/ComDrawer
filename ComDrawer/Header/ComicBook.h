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
//#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <fstream>
#include <QFileDialog>
#include <QPdfWriter>
#include <QTextDocument>
#include <QPainter>
#include <QPageSize>
#include <QMarginsF>
#ifdef _WIN32
#include <direct.h>  // For _mkdir on Windows
#else
#include <sys/stat.h>  // For mkdir on Linux/Unix
#endif


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
    void resizeEvent(QResizeEvent* event)override;

private slots:
    
    void addPage();
    void removePage();
    void pageSelect();
    void downloadComicBook();
    void nextPage();
    void prevPage();

private:
    void createActions();
    void createMenus();
    void readTextFile();
    void uploadImage(int panel, std::string filename, QGridLayout* page);
    void setPageNumber(int newPage);
    bool removeEntry();
    void modifyConfigurationFile(std::string entryToChange, std::string replacementText);
    void updatePageNumber();

    QAction* pagesAct;
    QAction* addPageAct;
    QAction* removePageAct;
    QAction* downloadComicAct;
    QAction* nextPageAct;
    QAction* prevPageAct;
    QMenu* fileMenu;
    Ui::ComicBook ui;
    QWidget* comicBookArea;
    int maxPages = 37;
    int minPages = 3;
    int defaultPages = 5;
    int currentPage = 0;
    int coverPage = 0;
    int pageCount;
    int maxPanelCount;
    int backPage = 4;
    QString _activeComicBook;
    std::string _activeComicBookConfigurationFile;
    int _maxWidth;
    int _maxHeight;
    int _panelWidth;
    int _panelHeight;

};

