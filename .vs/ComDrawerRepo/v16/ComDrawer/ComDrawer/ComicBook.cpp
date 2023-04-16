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
	comicBookArea = new QWidget();
	maxPanelCount = ((pageCount - 2) * 6) + 2;
	resize(500, 500);
}

/*
* Class Destructor.
*/
ComicBook::~ComicBook()
{
	delete comicBookArea;
}

/*
* Refreshes the screen. Currently does nothing.
*/
void ComicBook::refresh()
{
	if (comicBookArea->layout())
	{
		int count = 0;
		while (1)
		{
			QLayoutItem* item = comicBookArea->layout()->itemAt(count++);
			if (item)
			{
				comicBookArea->layout()->removeItem(item);
				QWidget* widget = item->widget();
				do
				{
					if (widget)
					{
						delete widget;
						widget = item->widget();
					}
					else
					{
						break;
					}
				} while (1);
				delete item;
			}
			else
			{
				delete item;
				delete comicBookArea->layout();
				break;
			}
		}
		
	}
	readTextFile(_activeComicBookConfigurationFile);
}

/*
* Selects the page.
*/
void ComicBook::pageSelect()
{
	bool status = false;
	std::string pageText = "Enter Page Number (0-" + std::to_string(backPage) +")";
	int page = QInputDialog::getInt(this, tr("ComDrawer"),
		pageText.c_str(),
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
	if (pageCount < maxPages)
	{
		pageCount++;
		backPage++;
		maxPanelCount = ((pageCount - 2) * 6) + 2;
	}
	else
	{
		QMessageBox::critical(this, tr("ComDrawer"), tr("<p>Max number of pages reached. No more can be added</p>"));
	}
}

/*
* Removes the page. Currently does nothing.
*/
void ComicBook::removePage()
{
	if (pageCount > minPages)
	{
		removeEntry();
		pageCount--;
		backPage--;
		maxPanelCount = ((pageCount - 2) * 6) + 2;
	}
	else
	{
		QMessageBox::critical(this, tr("ComDrawer"), tr("<p>Minimum number of pages reached. No more can be removed!</p>"));
	}
}

int ComicBook::getPanelCount()
{
	return maxPanelCount;
}

void ComicBook::downloadComicBook()
{

}

/*
* Create the actions for the ComicBook Window.
*/
void ComicBook::createActions()
{
	addPageAct = new QAction(tr("&Add Page"), this);
	connect(addPageAct, SIGNAL(triggered()), SLOT(addPage()));
	removePageAct = new QAction(tr("&Remove Page"), this);
	connect(removePageAct, SIGNAL(triggered()), SLOT(removePage()));
	pagesAct = new QAction(tr("&Select Page"), this);
	connect(pagesAct, SIGNAL(triggered()), SLOT(pageSelect()));
	downloadComicAct = new QAction(tr("&Download Comic"), this);
	connect(downloadComicAct, SIGNAL(triggered()), SLOT(downloadComicBook()));
}

/*
* Create the menu for the comicbook window. 
*/
void ComicBook::createMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(downloadComicAct);
	menuBar()->addMenu(fileMenu);
	menuBar()->addAction(addPageAct);
	menuBar()->addAction(removePageAct);
	menuBar()->addAction(pagesAct);
}

void ComicBook::readTextFile(std::string comicTitle)
{
	

	QGridLayout* page = new QGridLayout();
	int panelValues = 0;
	std::string mainPanels = "";
	int multipanel = 0;
	bool sixPanel = false;
	std::ifstream fin;
	std::string search;
	int count = 6;
	int panelId;
	bool found;
	if (currentPage == coverPage)
	{
		mainPanels = "cover";
		panelValues = 0;
	}
	else if (currentPage == backPage)
	{
		mainPanels = "end";
		panelValues = maxPanelCount;
	}
	else
	{
		panelValues = (currentPage * 6) + 1;
		sixPanel = true;
	}


	while (count > 0)
	{
		found = false;
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
			search = "panelId=" + mainPanels;
		}
		fin.open(_activeComicBookConfigurationFile);
		if (fin.fail())
		{
			break;
		}
		
		while (!fin.eof())
		{
			std::string temp = "";
			getline(fin, temp);
			auto t = temp.find(search) != std::string::npos;
			
			if (t)
			{
				std::string filename = temp.substr(search.size() + 1, temp.size() - 1);
				uploadImage(panelId, filename, page);
				found = true;
				break;
			}
		}
		fin.close();
		if (!found)
		{
			std::string blankPanel = "C:/Projects/Final_Project/ComDrawer/.vs/ComDrawerRepo/v16/ComDrawer/ComDrawer/blankPanel.png";
			uploadImage(panelId, blankPanel, page);
		}
		if (!sixPanel)
		{
			break;
		}
	}


		
}

void ComicBook::uploadImage(int panel, std::string filename, QGridLayout* page)
{
	QImage panelImage(filename.c_str());
	QLabel* imageLabel = new QLabel();
	imageLabel->setPixmap(QPixmap::fromImage(panelImage));
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
	comicBookArea->setLayout(page);
	setCentralWidget(comicBookArea);



}

void ComicBook::setPageNumber(int newPage)
{
	currentPage = newPage;
}

void ComicBook::createComicBook()
{
	bool status;
	QString text = QInputDialog::getText(this, tr("ComDrawer - Create Comic"), tr("Enter Comic Book name."),QLineEdit::Normal,tr(""),&status);
	if (status && !text.isEmpty())
	{
		std::string dir = text.toStdString();
		dir.erase(std::remove_if(dir.begin(), dir.end(), ::isspace), dir.end());
		if (mkdir(dir.c_str()) == -1)
		{
			QMessageBox::critical(
				this,
				tr("ComDrawer"),
				tr("Comic Book Creation Failed: Directory could not be created."));
			return;
		}
		
		std::ofstream fin;
		_activeComicBook = text;
		_activeComicBookConfigurationFile = dir + "/" + _activeComicBook.toStdString() + "_proj.txt";
		fin.open(_activeComicBookConfigurationFile);

		if (fin.fail())
		{
			QMessageBox::critical(
				this,
				tr("ComDrawer"),
				tr("Comic Book Creation Failed: Failed to create project configuration file"));
			return;
		}
		std::string comicNameHeader = "Comic Book Name:" + _activeComicBook.toStdString() + "\n";
		std::string comicPageCount = "Comic Book Page Count:" + std::to_string(pageCount) + "\n";
		fin.write(comicNameHeader.c_str(), comicNameHeader.size());
		fin.write(comicPageCount.c_str(), comicPageCount.size());
		fin.close();
	}
}

QString ComicBook::getActiveComicBook()
{
	return _activeComicBook;
}

void ComicBook::openComicBook()
{

}
std::string ComicBook::getActiveComicBookConfigurationFile()
{
	return _activeComicBookConfigurationFile;
}

bool ComicBook::removeEntry()
{
	bool status = false;
	std::ifstream fin;
	std::ofstream fout;
	int count = 6;


	int panelValues = (backPage * 6) + 1;
	int panelId;
	std::string search = "";
	std::string temp = "";
	while (count > 0)
	{
		bool found = false;

		panelId = (panelValues - count--);
		if (panelId <= panelValues)
			search = "panelId=" + std::to_string(panelId);
		else
			break;

		fin.open(_activeComicBookConfigurationFile);

		if (fin.fail())
		{
			status = false;
			break;
		}

		fout.open("temp.txt");

		if (fout.fail())
		{
			status = false;
			break;
		}
		status = true;
		while (getline(fin, temp))
		{
			temp.replace(temp.find(search), search.length(), "");
			fout.write(temp.c_str(), temp.size());

		}
		fin.close();
		fout.close();
		remove(_activeComicBookConfigurationFile.c_str());
		rename("temp.txt", _activeComicBookConfigurationFile.c_str());
	}


	return status;
}