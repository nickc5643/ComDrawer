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
void ComDrawer::selectDesignTool(int selection)
{
	canvasView->setWorkingToolSelection(selection);
}

/*
	Creates the action commands, currenlty supports:
		- about
*/
void ComDrawer::createActions()
{
	aboutAct = new QAction(tr("&About"), this);
	connect(aboutAct, SIGNAL(triggered()), SLOT(about()));
	pencil = new QAction(tr("&Pencil"), this);
	connect(aboutAct, SIGNAL(triggered()), SLOT(selectDesignTool((0))));
	toolOptions.append(pencil);
}

/*
* Creates the menus.
*/
void ComDrawer::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	toolsMenu = new QMenu(tr("&Tools"), this);
	for (QAction* action : std::as_const(toolOptions))
		toolsMenu->addAction(action);

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