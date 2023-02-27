#include "ComicBook.h"

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

ComicBook::~ComicBook()
{
	delete refreshAct;
	delete pageSelectMenu;
}

void ComicBook::refresh()
{
}

void ComicBook::pageSelect()
{
}

void ComicBook::createActions()
{
	refreshAct = new QAction(tr("&Refresh Preview"), this);
	connect(refreshAct, SIGNAL(triggered()), SLOT(refresh()));

	addPageAct = new QAction(tr("&Add Page"), this);
	connect(addPageAct, SIGNAL(triggered()), SLOT(refresh()));

	for (int i = 0; i < defaultPages; i++)
	{
		QAction* tempAct;
		if (i == 0)
		{
			tempAct  = new QAction(tr("&Cover Page"), this);
		}
		else if (i == maxPages - 1)
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

void ComicBook::createMenus()
{
	pageSelectMenu = new QMenu(tr("&Select Page"), this);
	for (QAction* action : pagesAct)
	{
		pageSelectMenu->addAction(action);
	}
	menuBar()->addAction(refreshAct);
	menuBar()->addMenu(pageSelectMenu);
}