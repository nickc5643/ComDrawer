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
	void selectFill();
	void selectStraightLine();
	void setColor();
	void setWidth();

private:	
	CanvasView* canvasView;
	void createActions();
	void createMenus();
	QAction* openAct;
    Ui::ComDrawerClass ui;
	QMenu *fileMenu;
	QMenu* toolsMenu;
	QMenu* helpMenu;
	QMenu* plotMenu;
	QMenu* openTemplateMenu;
	QAction* open;
	QAction *aboutAct;
	QAction* pencilAct;
	QAction* eraserAct;
	QAction* paintAct;
	QAction* fillAct;
	QAction* colorAct;
	QAction* widthAct;
	QAction* straightLineAct;
	QList<QAction*> toolOptions;
};
