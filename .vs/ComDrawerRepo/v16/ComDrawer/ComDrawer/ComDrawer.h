#pragma once

#include <QtWidgets/QWidget>
#include "ui_ComDrawer.h"
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
#include "ComicBook.h"

/*
* The purpose of this class is to control the main ComDrawer widget. 
*/

class ComDrawer : public QMainWindow
{
    Q_OBJECT

public:
    ComDrawer(QWidget *parent = nullptr);
    ~ComDrawer();

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void about();
	void selectPencil();
	void selectEraser();
	void selectPaint();
	void selectTextBox();
	void setColor();
	void setWidth();
	void clearActiveScreen();
	void openComicBookPreview();
	void setPanel();
	void savePanel();
	void openPanel();
	void newPanel();
	void createComic();
	void openComic();
	void selectDefaultElement();
	void selectCustomElement();
	void saveElement();

private:	
	void createActions();
	void createMenus();

	CanvasView* canvasView;
	ComicBook* comicBook;
	Ui::ComDrawerClass ui;

	QAction* _openAct;
	QMenu* fileMenu;
	QMenu* _toolsMenu;
	QMenu* _helpMenu;
	QMenu* _plotMenu;
	QMenu* _openTemplateMenu;
	QMenu* _elementMenu;
	QAction* open;
	QAction *_aboutAct;
	QAction* _pencilAct;
	QAction* _eraserAct;
	QAction* _paintAct;
	QAction* _textboxAct;
	QAction* _colorAct;
	QAction* _widthAct;
	QAction* _clearAct;
	QAction* _previewComicAct;
	QAction* _setPanelAct;
	QList<QAction*> _toolOptions;
	QAction* _savePanelAct;
	QAction* _openComicAct;
	QAction* _createComicAct;
	QAction* _openPanelAct;
	QAction* _newPanelAct;
	QAction* _defaultElementAct;
	QAction* _customElementAct;
	QAction* _newCustomElementAct;

};
