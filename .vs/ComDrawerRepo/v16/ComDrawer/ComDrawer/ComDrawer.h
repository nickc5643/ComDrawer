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
#include <QUndoStack>
#include <QUndoView>
#include <QDockWidget>
#include <QGraphicsScene>
#include <QUndoCommand>
#include "ComicBook.h"
#include "CardMaster.h"
#include <QTextEdit>

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
	void openPNG();
	void createUndoView();
	void createEventLogViewer();
	void previewCardList();
	void createCardDesp();
	void createCardList();
	void openCardList();
	void setCardTitle();
	void saveCard();
	void modifyElementSize();
	void selectStraightLine();

private:	
	void createActions();
	void createMenus();

	CanvasView* canvasView;
	ComicBook* comicBook;
	CardMaster* cardMaster;
	Ui::ComDrawerClass ui;

	QAction* _openAct;
	QMenu* fileMenu;
	QMenu* _toolsMenu;
	QMenu* _helpMenu;
	QMenu* _plotMenu;
	QMenu* _openTemplateMenu;
	QMenu* _elementMenu;
	QMenu* _developerMenu;
	QMenu* _cardViewMenu;
	QAction* open;
	QAction *_aboutAct;
	QAction* _pencilAct;
	QAction* _straightLineAct;
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
	QAction* _undoAction;
	QAction* _redoAction;
	QAction* _pngUploaderAct;
	QAction* _eventLogViewAct;
	QAction* _undoViewAct;
	QAction* _cardViewAct;
	QAction* _createDeckAct;
	QAction* _openDeckAct;
	QAction* _cardDespAct;
	QAction* _setCardTitle;
	QAction* _saveCardAct;
	QAction* _modifyElementAct;


	QUndoView* _undoView;

};
