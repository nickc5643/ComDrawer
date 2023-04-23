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
	delete _toolsMenu;
	delete _plotMenu;
	delete _helpMenu;
	delete _aboutAct;
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
	QMessageBox::about(this, tr("ComDrawer Version 1.0.0"), tr("<p> The ComDrawer is meant to allow the user to create their own comic book</p>"));
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
* Selects the Text Box tool.
*/
void ComDrawer::selectTextBox()
{
	canvasView->setWorkingToolSelection(3);
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
	if (comicBook->getActiveComicBook() == "")
	{
		QMessageBox::critical(
			this,
			tr("ComDrawer"),
			tr("Please open or create a comic book."));
		return;
	}
	canvasView->setMaxPanel(comicBook->getPanelCount());
	comicBook->setMaximumHeight(900);
	comicBook->setMaximumWidth(1800);
	comicBook->resize(1800, 900);
	comicBook->refresh();
	comicBook->show();
}

/*
* Sets the panel.
*/
void ComDrawer::setPanel()
{

	if (comicBook->getActiveComicBook() == "")
	{
		QMessageBox::critical(
			this,
			tr("ComDrawer"),
			tr("Please open or create a comic book."));
		return;
	}
	canvasView->setMaxPanel(comicBook->getPanelCount());
	if (canvasView->setPanel(comicBook->getActiveComicBookConfigurationFile()))
		comicBook->refresh();
}

/*
* Saves the panel
*/
void ComDrawer::savePanel()
{
	canvasView->saveMyPanel();
}

/*
* Opens the panel.
*/
void ComDrawer::openPanel()
{
	canvasView->openPanel();
}

/*
* Creates a new panel.
*/
void ComDrawer::newPanel()
{
	canvasView->newPanel();
}

/*
* Creates a new comic book.
*/
void ComDrawer::createComic()
{
	comicBook->createComicBook();
}

/*
* Opens the comic book.
*/
void ComDrawer::openComic()
{
	comicBook->openComicBook();
}

/*
* Alllows the user to select a default element.
*/
void ComDrawer::selectDefaultElement()
{
	canvasView->selectDefaultElement();
}

/*
* Selects the custom elements.
*/
void ComDrawer::selectCustomElement()
{
	canvasView->selectCustomElement();
}

/*
* Saves the element 
*/
void ComDrawer::saveElement()
{
	canvasView->saveElement();
}

/*
	Creates the action commands, currenlty supports:
		- about
*/
void ComDrawer::createActions()
{
	_aboutAct = new QAction(tr("&About"), this);
	connect(_aboutAct, SIGNAL(triggered()), SLOT(about()));
	_clearAct = new QAction(tr("&Clear Design"), this);
	connect(_clearAct, SIGNAL(triggered()), SLOT(clearActiveScreen()));
	_previewComicAct = new QAction(tr("&Preview ComicBook"), this);
	connect(_previewComicAct, SIGNAL(triggered()), SLOT(openComicBookPreview()));

	_pencilAct = new QAction(tr("&Pencil"), this);
	connect(_pencilAct, SIGNAL(triggered()), SLOT(selectPencil()));
	_eraserAct = new QAction(tr("&Eraser"), this);
	connect(_eraserAct, SIGNAL(triggered()), SLOT(selectEraser()));
	_paintAct = new QAction(tr("&Paint Brush"), this);
	connect(_paintAct, SIGNAL(triggered()), SLOT(selectPaint()));
	_textboxAct = new QAction(tr("&Enter Text"), this);
	connect(_textboxAct, SIGNAL(triggered()), SLOT(selectTextBox()));
	_colorAct = new QAction(tr("&Change Color"), this);
	_colorAct->setShortcut(tr("ctrl+f"));
	connect(_colorAct, SIGNAL(triggered()), SLOT(setColor()));
	_widthAct = new QAction(tr("&Change Width"), this);
	_widthAct->setShortcut(tr("ctrl+d"));
	connect(_widthAct, SIGNAL(triggered()), SLOT(setWidth()));
	_toolOptions.append(_pencilAct);
	_toolOptions.append(_paintAct);
	_toolOptions.append(_eraserAct);
	_toolOptions.append(_textboxAct);
	_toolOptions.append(_colorAct);
	_toolOptions.append(_widthAct);
	_setPanelAct = new QAction(tr("&Set Panel"), this);
	connect(_setPanelAct, SIGNAL(triggered()), SLOT(setPanel()));

	_savePanelAct = new QAction(tr("Save Panel"));
	_savePanelAct->setShortcut(tr("ctrl+s"));
	connect(_savePanelAct, SIGNAL(triggered()), SLOT(savePanel()));

	_newCustomElementAct = new QAction(tr("Save Custom Element"));
	_newCustomElementAct->setShortcut(tr("ctrl+e"));
	connect(_newCustomElementAct, SIGNAL(triggered()), SLOT(saveElement()));

	_openPanelAct = new QAction(tr("Open Panel"));
	connect(_openPanelAct, SIGNAL(triggered()), SLOT(openPanel()));
	_newPanelAct = new QAction(tr("New Panel"));
	connect(_newPanelAct, SIGNAL(triggered()), SLOT(newPanel()));

	_createComicAct = new QAction(tr("New Comic"));
	_createComicAct->setShortcut(tr("ctrl+n"));
	connect(_createComicAct, SIGNAL(triggered()), SLOT(createComic()));
	_openComicAct = new QAction(tr("Open Comic"));
	_openComicAct->setShortcut(tr("ctrl+o"));
	connect(_openComicAct, SIGNAL(triggered()), SLOT(openComic()));

	_defaultElementAct = new QAction(tr("Default Element"));
	connect(_defaultElementAct, SIGNAL(triggered()), SLOT(selectDefaultElement()));
	_customElementAct = new QAction(tr("Custom Element"));
	connect(_customElementAct, SIGNAL(triggered()), SLOT(selectCustomElement()));

	
}

/*
* Creates the menus.
*/
void ComDrawer::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(_savePanelAct);
	fileMenu->addAction(_newCustomElementAct);
	fileMenu->addSeparator();
	fileMenu->addAction(_openPanelAct);
	fileMenu->addAction(_newPanelAct);
	fileMenu->addSeparator();
	fileMenu->addAction(_openComicAct);
	fileMenu->addAction(_createComicAct);
	
	
	_toolsMenu = new QMenu(tr("&Tools"), this);
	int counter = 0;
	for (QAction* action : _toolOptions)
	{
		if (action == _colorAct)
		{
			_toolsMenu->addSeparator();
		}
		_toolsMenu->addAction(action);

	}
	_pencilAct->setChecked(true);
		

	_plotMenu = new QMenu(tr("&Set Panel"), this);
	_helpMenu = new QMenu(tr("&Help"), this);
	_helpMenu->addAction(_aboutAct);
	
	_elementMenu = new QMenu(tr("&Elements"));
	_elementMenu->addAction(_defaultElementAct);
	_elementMenu->addAction(_customElementAct);


	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(_toolsMenu);
	menuBar()->addMenu(_elementMenu);
	menuBar()->addAction(_setPanelAct);
	menuBar()->addAction(_previewComicAct);
	menuBar()->addAction(_clearAct);
	menuBar()->addMenu(_helpMenu);
}