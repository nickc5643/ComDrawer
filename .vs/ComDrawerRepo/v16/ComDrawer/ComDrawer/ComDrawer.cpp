#include "ComDrawer.h"


/*
* Class constructor.
*/
ComDrawer::ComDrawer(QWidget* parent)
{
	
	createActions();
	createMenus();
	canvasView = new CanvasView();

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
	delete openTemplateMenu;
	delete helpMenu;
	delete aboutAct;
	delete canvasView;
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
* Selects the design tool the user wants to use.
* @param[in] - selection - interger that references a certain item.
*/
void ComDrawer::selectPencil()
{
	canvasView->setWorkingToolSelection(0);
}

void ComDrawer::selectPaint()
{
	canvasView->setWorkingToolSelection(1);
}

void ComDrawer::selectEraser()
{
	canvasView->setWorkingToolSelection(2);
}

void ComDrawer::selectFill()
{
	canvasView->setWorkingToolSelection(3);
}

void ComDrawer::selectStraightLine()
{
	canvasView->setWorkingToolSelection(4);
}

void ComDrawer::setColor() 
{
	canvasView->setColor();	
}

void ComDrawer::setWidth()
{
	canvasView->setWidth();
}

void ComDrawer::clearActiveScreen()
{
	canvasView->clearActiveScreen();
}
void ComDrawer::openComicBookPreview()
{
	ComicBook* comicBook = new ComicBook();
	comicBook->show();
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
	connect(colorAct, SIGNAL(triggered()), SLOT(setColor()));
	widthAct = new QAction(tr("&Change Width"), this);
	connect(widthAct, SIGNAL(triggered()), SLOT(setWidth()));
	toolOptions.append(pencilAct);
	toolOptions.append(paintAct);
	toolOptions.append(eraserAct);
	toolOptions.append(fillAct);
	toolOptions.append(straightLineAct);
	toolOptions.append(colorAct);
	toolOptions.append(widthAct);
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
		

	plotMenu = new QMenu(tr("&Select Panel"), this);
	helpMenu = new QMenu(tr("&Help"), this);
	helpMenu->addAction(aboutAct);
	elements = new QMenu(tr("&Elements"), this);
	
	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(toolsMenu);
	menuBar()->addMenu(plotMenu);
	menuBar()->addAction(previewComicAct);
	menuBar()->addAction(clearAct);
	menuBar()->addMenu(elements);
	menuBar()->addMenu(helpMenu);
}