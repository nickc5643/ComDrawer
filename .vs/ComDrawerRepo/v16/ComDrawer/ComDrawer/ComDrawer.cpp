#include "ComDrawer.h"


/*
* Class constructor.
*/
ComDrawer::ComDrawer(QWidget* parent)
{
	
	createActions();
	createMenus();
	canvasView = new CanvasView();
	comicBook = new ComicBook();
	ui.setupUi(this);
	setWindowTitle(tr("ComDrawer - Canvas View"));
	
	
	setCentralWidget(canvasView);
	

	resize(500, 500);
}

/*
	Class Destructor.
*/
ComDrawer::~ComDrawer() 
{
	delete fileMenu;
	delete toolsMenu;
	delete plotMenu;
	delete helpMenu;
	delete aboutAct;
	delete canvasView;
	delete comicBook;
}

/*
*	Close event.
*   param[in] - event - close event
*/
void ComDrawer::closeEvent(QCloseEvent *event)
{
	//Do nothing for now.
}

/*
* The about message.
*/
void ComDrawer::about() 
{
	QMessageBox::about(this, tr("ComDrawer Version 0.0.1"), tr("<p> The ComDrawer is meant to allow the user to create their own comic book</p>"));
}

/*
* Selects the pencil tool.
*/
void ComDrawer::selectPencil()
{
	canvasView->setWorkingToolSelection(0);
}

/*
* Selects the paint tool.
*/
void ComDrawer::selectPaint()
{
	canvasView->setWorkingToolSelection(1);
}

/*
* Selects the eraser tool.
*/
void ComDrawer::selectEraser()
{
	canvasView->setWorkingToolSelection(2);
}

/*
* Selects the fill can tool.
*/
void ComDrawer::selectFill()
{
	canvasView->setWorkingToolSelection(3);
}

/*
* Selects the stright line tool.
*/
void ComDrawer::selectStraightLine()
{
	canvasView->setWorkingToolSelection(4);
}

/*
* Calls canvasView's setColor.
*/
void ComDrawer::setColor() 
{
	canvasView->setColor();	
}

/*
* Calls canvasView's setWidth.
*/
void ComDrawer::setWidth()
{
	canvasView->setWidth();
}

/*
* Calls canvasView's clearActiveScreen.
*/
void ComDrawer::clearActiveScreen()
{
	canvasView->clearActiveScreen();
}

/*
* Creates the comicbook window.
*/
void ComDrawer::openComicBookPreview()
{
	canvasView->setMaxPanel(comicBook->getPanelCount());
	comicBook->show();
}

void ComDrawer::setPanel()
{
	if (canvasView->setPanel())
		comicBook->refresh();
}



/*
	Creates the action commands, currenlty supports:
		- about
*/
void ComDrawer::createActions()
{
	aboutAct = new QAction(tr("&About"), this);
	connect(aboutAct, SIGNAL(triggered()), SLOT(about()));
	clearAct = new QAction(tr("&Clear Design"), this);
	connect(clearAct, SIGNAL(triggered()), SLOT(clearActiveScreen()));
	previewComicAct = new QAction(tr("&Preview ComicBook"), this);
	connect(previewComicAct, SIGNAL(triggered()), SLOT(openComicBookPreview()));

	pencilAct = new QAction(tr("&Pencil"), this);
	connect(pencilAct, SIGNAL(triggered()), SLOT(selectPencil()));
	eraserAct = new QAction(tr("&Eraser"), this);
	connect(eraserAct, SIGNAL(triggered()), SLOT(selectEraser()));
	paintAct = new QAction(tr("&Paint Brush"), this);
	connect(paintAct, SIGNAL(triggered()), SLOT(selectPaint()));
	fillAct = new QAction(tr("&Fill Can"), this);
	connect(fillAct, SIGNAL(triggered()), SLOT(selectFill()));
	straightLineAct = new QAction(tr("&Straight Line"), this);
	connect(straightLineAct, SIGNAL(triggered()), SLOT(selectStraightLine()));
	colorAct = new QAction(tr("&Change Color"), this);
	colorAct->setShortcut(tr("ctrl+f"));
	connect(colorAct, SIGNAL(triggered()), SLOT(setColor()));
	widthAct = new QAction(tr("&Change Width"), this);
	widthAct->setShortcut(tr("ctrl+d"));
	connect(widthAct, SIGNAL(triggered()), SLOT(setWidth()));
	toolOptions.append(pencilAct);
	toolOptions.append(paintAct);
	toolOptions.append(eraserAct);
	toolOptions.append(fillAct);
	toolOptions.append(straightLineAct);
	toolOptions.append(colorAct);
	toolOptions.append(widthAct);
	setPanelAct = new QAction(tr("&Set Panel"), this);
	connect(setPanelAct, SIGNAL(triggered()), SLOT(setPanel()));
	
}

/*
* Creates the menus.
*/
void ComDrawer::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	toolsMenu = new QMenu(tr("&Tools"), this);
	int counter = 0;
	for (QAction* action : toolOptions)
	{
		if (action == colorAct)
		{
			toolsMenu->addSeparator();
		}
		toolsMenu->addAction(action);

	}
	pencilAct->setChecked(true);
		

	plotMenu = new QMenu(tr("&Set Panel"), this);
	helpMenu = new QMenu(tr("&Help"), this);
	helpMenu->addAction(aboutAct);
	
	
	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(toolsMenu);
	menuBar()->addAction(setPanelAct);
	menuBar()->addAction(previewComicAct);
	menuBar()->addAction(clearAct);
	menuBar()->addMenu(helpMenu);
}