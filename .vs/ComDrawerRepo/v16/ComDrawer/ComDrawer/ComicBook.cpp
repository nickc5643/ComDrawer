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
	currentPage = 0;
	refreshPage = false;
	comicBookArea = new QWidget();
	setCentralWidget(comicBookArea);
	maxPanelCount = ((pageCount - 2) * 6) + 2;
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
	pageCount++;
}

/*
* Removes the page. Currently does nothing.
*/
void ComicBook::removePage()
{
	pageCount--;
}

int ComicBook::getPanelCount()
{
	return maxPanelCount;
}

/*
* Create the actions for the ComicBook Window.
*/
void ComicBook::createActions()
{
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
	menuBar()->addAction(addPageAct);
	menuBar()->addAction(removePageAct);
	menuBar()->addMenu(pageSelectMenu);
}

void ComicBook::readTextFile()
{
	int panelValues = 0;
	int multipanel = 0;
	bool sixPanel = false;
	if (currentPage == coverPage)
	{
		panelValues = 0;
	}
	else if (currentPage == backPage)
	{
		panelValues = backPage;
	}
	else
	{
		panelValues = (currentPage * 6) + 1;
		sixPanel = true;
	}
	std::ifstream fin;
	fin.open("example.txt");
	if (fin.fail())
	{
		return;
	}

	std::string search;
	int count = 6;
	int panelId;
	while (!fin.eof())
	{
		if (sixPanel)
		{
			panelId = (panelValues - count--);
			if (panelId <= panelValues)
				search = "panelId=" + panelId;
			else
				break;
		}
		else
		{
			panelId = panelValues;
			search = "panelId=" + panelId;
		}

		std::string temp = "";
		getline(fin, temp);
		if (temp.find(search))
		{
			std::string filename = temp.substr(search.size() + 1, temp.size() - 1);
			uploadImage(panelId, filename);
		}

		if (!sixPanel)
		{
			break;
		}
	}
	

		
}

void ComicBook::uploadImage(int panel, std::string filename)
{
	//do nothing
}