#include "ComicBook.h"

/*
* Class constructor.
*/
ComicBook::ComicBook(QWidget* parent)
{
	createActions();
	createMenus();
	ui.setupUi(this);
	setWindowTitle(tr("ComDrawer - Comic Book Preview"));
	comicBookArea = new QWidget();
	setCentralWidget(comicBookArea);
	resize(500, 500);
}

/*
* Class Destructor.
*/
ComicBook::~ComicBook()
{
	delete refreshAct;
	delete pageSelectMenu;
}

/*
* Refreshes the screen. Currently does nothing.
*/
void ComicBook::refresh()
{
}

/*
* Selects the page. Currently does nothing.
*/
void ComicBook::pageSelect()
{
}

/*
* Adds the page. Currently does nothing.
*/
void ComicBook::addPage() 
{

}

/*
* Removes the page. Currently does nothing.
*/
void ComicBook::removePage()
{

}

/*
* Create the actions for the ComicBook Window.
*/
void ComicBook::createActions()
{
	refreshAct = new QAction(tr("&Refresh Preview"), this);
	connect(refreshAct, SIGNAL(triggered()), SLOT(refresh()));

	addPageAct = new QAction(tr("&Add Page"), this);
	connect(addPageAct, SIGNAL(triggered()), SLOT(addPage()));

	removePageAct = new QAction(tr("&Remove Page"), this);
	connect(removePageAct, SIGNAL(triggered()), SLOT(addPage()));

	for (int i = 0; i < defaultPages; i++)
	{
		QAction* tempAct;
		if (i == 0)
		{
			tempAct  = new QAction(tr("&Cover Page"), this);
		}
		else if (i == defaultPages - 1)
		{
			tempAct = new QAction(tr("&Back Page"), this);
		}
		else
		{
			tempAct = new QAction(QString::number(i), this);
		}
		connect(tempAct, SIGNAL(triggered()), SLOT(pageSelect()));
		pagesAct.append(tempAct);
	}
}

/*
* Create the menu for the comicbook window. 
*/
void ComicBook::createMenus()
{
	pageSelectMenu = new QMenu(tr("&Select Page"), this);
	for (QAction* action : pagesAct)
	{
		pageSelectMenu->addAction(action);
	}
	menuBar()->addAction(refreshAct);
	menuBar()->addAction(addPageAct);
	menuBar()->addAction(removePageAct);
	menuBar()->addMenu(pageSelectMenu);
}