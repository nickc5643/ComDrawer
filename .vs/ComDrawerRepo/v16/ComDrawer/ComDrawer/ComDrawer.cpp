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
	setWindowTitle(tr("ComDrawer"));
	
	
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
	QColor newColor = QColorDialog::getColor(canvasView->penColor());
	if (newColor.isValid())
		canvasView->setPaintCololr(newColor);
}

void ComDrawer::setWidth()
{
	
	bool ok;
	int newWidth = 0;
	if (canvasView->getWorkingTool() == 1)
	{
		newWidth = QInputDialog::getInt(this, tr("ComDrawer"),
			tr("Select paint width:"),
			canvasView->penWidth(),
			1, 50, 1, &ok);
		if (ok)
			canvasView->setPaintWidth(newWidth);
	}
	else if (canvasView->getWorkingTool() == 2)
	{
		newWidth = QInputDialog::getInt(this, tr("ComDrawer"),
			tr("Select eraser width:"),
			canvasView->getEraserWidth(),
			1, 50, 1, &ok);
		if (ok)
			canvasView->setEraserWidth(newWidth);
	}
	else
	{
		QMessageBox::about(this, tr("ComDrawer"), tr("<p> Only the paint brush and eraser can change widths.</p>"));
	}

}

/*
	Creates the action commands, currenlty supports:
		- about
*/
void ComDrawer::createActions()
{
	aboutAct = new QAction(tr("&About"), this);
	connect(aboutAct, SIGNAL(triggered()), SLOT(about()));
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
		

	plotMenu = new QMenu(tr("&Select Panel"), this);
	openTemplateMenu = new QMenu(tr("&View/Edit Comic"), this);
	helpMenu = new QMenu(tr("&Help"), this);
	helpMenu->addAction(aboutAct);

	
	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(toolsMenu);
	menuBar()->addMenu(plotMenu);
	menuBar()->addMenu(openTemplateMenu);
	menuBar()->addMenu(helpMenu);
}