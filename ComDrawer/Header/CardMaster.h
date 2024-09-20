#pragma once
#include <QtWidgets/QWidget>
#include "ui_CardMaster.h"
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
#ifdef _WIN32
#include <direct.h>  // For _mkdir on Windows
#else
#include <sys/stat.h>  // For mkdir on Linux/Unix
#endif


/*
* The purpose of this class is to control the main ComDrawer widget.
*/

class CardMaster : public QMainWindow
{
    Q_OBJECT

public:
    CardMaster();
    void createCardList();
    void setCardTitle();
    void setCardDescription();
    void openCardList();
    void refresh();
    

    

private:
    void createActions();
    void createMenus();
    void readTextFile();


    QString _cardTitle;
    QString _cardDesp;
    QString _cardFilename;
    std::string _cardList;
    QString _activeCardList;
    std::string _activeCardConfigurationFile;
    int _cardCount;
    Ui::CardMaster ui;
    QWidget* _cardDisplayArea;
    int _maxWidth;
    int _maxHeight;





};