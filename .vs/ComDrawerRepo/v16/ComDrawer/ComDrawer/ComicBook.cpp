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
	//QLabel* imageLabel = new QLabel();

	//QImage image("C:/Projects/Final_Project/ComDrawer/.vs/ComDrawerRepo/v16/ComDrawer/ComDrawer/test/Test_Image.png");
	//imageLabel->setPixmap(QPixmap::fromImage(image));
	//QScrollArea* scrollArea = new QScrollArea;
	//scrollArea->setWidget(imageLabel);
	//setCentralWidget(scrollArea);
	readTextFile('0');
	maxPanelCount = ((pageCount - 2) * 6) + 2;
	resize(500, 500);
}

/*
* Class Destructor.
*/
ComicBook::~ComicBook()
{
	delete pageSelectMenu;
}

/*
* Refreshes the screen. Currently does nothing.
*/
void ComicBook::refresh()
{
	/*QLayoutItem* item = comicBookArea->layout()->itemAt(0);
	if (item)
	{
		comicBookArea->layout()->removeItem(item);
		QWidget* widget = item->widget();
		if (widget)
		{
			delete widget;
		}
	}*/
	readTextFile('0');
}

/*
* Selects the page. Currently does nothing.
*/
void ComicBook::pageSelect()
{
	bool status = false;
	int page = QInputDialog::getInt(this, tr("ComDrawer"),
		tr("Enter a page number 0 - " + backPage),
		currentPage,
		coverPage, backPage, currentPage, &status);
	if (status)
	{
		setPageNumber(page);
		refresh();
	}
}

/*
* Adds the page. Currently does nothing.
*/
void ComicBook::addPage() 
{
	pageCount++;
	backPage++;
}

/*
* Removes the page. Currently does nothing.
*/
void ComicBook::removePage()
{
	pageCount--; 
	backPage--;
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

void ComicBook::readTextFile(const char& comic_title)
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
				search = "panelId=" + std::to_string(panelId);
			else
				break;
		}
		else
		{
			panelId = panelValues;
			search = "panelId=" + std::to_string(panelId);;
		}

		std::string temp = "";
		getline(fin, temp);
		auto t = temp.find(search) != std::string::npos;
		if (t)
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
	QLabel* imageLabel = new QLabel();
	QImage image(filename.c_str());
	imageLabel->setPixmap(QPixmap::fromImage(image));
	QGridLayout* page = new QGridLayout();
	if (panel == coverPage)
	{
		page->addWidget(imageLabel, 0, 0, 3, 2);
	}
	else if (panel == backPage)
	{
		page->addWidget(imageLabel, 0, 0, 3, 2);
	}
	else
	{
		int panelKey = panel;
		if (panel > 6)
		{
			panelKey = (panel - 1) / 6;
		}
		
 		if (panelKey == 1)
		{
			page->addWidget(imageLabel, 0, 0, 1, 1);
		}
		else if (panelKey == 2)
		{
			page->addWidget(imageLabel, 0, 1, 1, 1);
		}
		else if (panelKey == 3)
		{
			page->addWidget(imageLabel, 1, 0, 1, 1);
		}
		else if (panelKey == 4)
		{
			page->addWidget(imageLabel, 1, 1, 1, 1);
		}
		else if (panelKey == 5)
		{
			page->addWidget(imageLabel, 2, 0, 1, 1);
		}
		else if (panelKey == 6)
		{
			page->addWidget(imageLabel, 2, 1, 1, 1);
		}

	}

	
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setWidget(imageLabel);
	comicBookArea->setLayout(page);
	setCentralWidget(comicBookArea);
}

void ComicBook::setPageNumber(int newPage)
{
	currentPage = newPage;
}