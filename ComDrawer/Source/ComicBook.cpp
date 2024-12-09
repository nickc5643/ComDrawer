#include "../Header/ComicBook.h"

/*
* Class constructor.
*/
ComicBook::ComicBook(QWidget* parent)
{
	createActions();
	createMenus();
	ui.setupUi(this);
	setWindowTitle(tr("ComDrawer - Comic Book Preview Cover Page"));
	currentPage = 0;
	pageCount = 5;
	comicBookArea = new QWidget();
	maxPanelCount = ((pageCount - 2) * 6) + 1;
	_maxWidth = 1500;
	_maxHeight = 900;
	_panelWidth = _maxWidth / 2;
	_panelHeight = _maxHeight / 3;
	
	//resize(500, 500);
}

/*
* Class Destructor.
*/
ComicBook::~ComicBook()
{
	delete comicBookArea;
}

/*
* Refreshes the preview window.
*/
void ComicBook::refresh()
{
	delete comicBookArea;
	comicBookArea = new QWidget();
	comicBookArea->resize(_maxWidth, _maxHeight);
	std::string pageValue = "ComDrawer - Comic Book Preview ";
	if (currentPage == coverPage)
	{
		pageValue += "Cover Page";
	}
	else if (currentPage == backPage)
	{
		pageValue += "Back Page";
	}
	else
	{
		pageValue += "Page Number: " + std::to_string(currentPage);
	}
	setWindowTitle(tr(pageValue.c_str()));
	readTextFile();
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
* Adds the page.
*/
void ComicBook::addPage() 
{
	if (pageCount < maxPages)
	{
		pageCount++;
		backPage++;
		maxPanelCount = ((pageCount - 2) * 6) + 1;
		updatePageNumber();
	}
	else
	{
		QMessageBox::critical(this, tr("ComDrawer"), tr("<p>Max number of pages reached. No more can be added</p>"));
	}
}

/*
* Removes the last page page. 
*/
void ComicBook::removePage()
{
	if (pageCount > minPages)
	{
		removeEntry();
		pageCount--;
		backPage--;
		maxPanelCount = ((pageCount - 2) * 6) + 1;
		updatePageNumber();
	}
	else
	{
		QMessageBox::critical(this, tr("ComDrawer"), tr("<p>Minimum number of pages reached. No more can be removed!</p>"));
	}
}

/*
* Returns the max panel count.
*/
int ComicBook::getPanelCount()
{
	return maxPanelCount;
}

/*
* Stores the comic book as a PDF File for the user to use.
*/
void ComicBook::downloadComicBook()
{
	QString filename = _activeComicBook + "Book.pdf";
	QPdfWriter writer(filename);
	writer.setPageSize(QPageSize(QPageSize::Letter)/*QPagedPaintDevice::Letter*/);
	writer.setPageMargins(QMargins(15, 15, 15, 15));
	QPainter painter(&writer);
	std::string panelId;
	std::string search;
	std::string imageToPost;
	std::ifstream fin;
	std::string imageFilename;
	int countPage = 0;
	int maxWidth = 9500;
	int maxHeight = 12500;
	int panelMaxWidth = 4725;
	int panelMaxHeight = 4141;
	QPen drawPen(Qt::black, 20);
	painter.setPen(drawPen);
	
	bool found;
	for (int i = 0; i <= maxPanelCount; i++)
	{
		panelId = "";
		found = false;
		imageFilename = "";
		if (i == 0)
		{
			panelId = "cover";
		}
		else if (i == maxPanelCount)
		{
			panelId = "end";
		}
		else
		{
			panelId = std::to_string(i);
		}
		search = "panelId=" + panelId;

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
				imageFilename = temp.substr(search.size() + 1, temp.size() - 1);
				found = true;
				break;
			}
		}
		fin.close();

		if (!found)
		{
			if (i == coverPage || i == maxPanelCount-1)
			{
				imageFilename = "blankCoverBackPanel.png";
			}
			else
			{
				imageFilename = "blankPanel.png";
			}
		}

		QImage imageToPublish(QString::fromStdString(imageFilename));

		if (i == coverPage)
		{
			imageToPublish = imageToPublish.scaled(maxWidth, maxHeight);
			painter.drawImage(0, 0, imageToPublish);
		}
		else if (i == maxPanelCount)
		{
			imageToPublish = imageToPublish.scaled(_maxWidth, _maxHeight, Qt::KeepAspectRatioByExpanding);
			painter.drawImage(0,0 , imageToPublish);
		}
		else
		{
			imageToPublish = imageToPublish.scaled(panelMaxWidth, panelMaxHeight);
	

			int panelKey = i;
			if (i > 6)
			{
				panelKey = i - (6 * (countPage - 1));
			}

			if (panelKey == 1)
			{
				painter.drawImage(0, 0, imageToPublish);
				painter.drawLine(0,4166,9500,4166);//Horizontal line
				painter.drawLine(4750, 0, 4750, 12498);

			}
			else if (panelKey == 2)
			{
				painter.drawImage(4752, 0, imageToPublish);

			}
			else if (panelKey == 3)
			{
				painter.drawImage(0, 4167, imageToPublish);
				painter.drawLine(0, 8332, 9500, 8332);
			}
			else if (panelKey == 4)
			{
				painter.drawImage(4752, 4167, imageToPublish);
			}
			else if (panelKey == 5)
			{
				painter.drawImage(0, 8334, imageToPublish);
				painter.drawLine(0, 12498, 9500, 12498);
			}
			else if (panelKey == 6)
			{
				painter.drawImage(4752, 8334, imageToPublish);
			}
		}
		if (i % 6 == 0)
		{
			writer.newPage();
			countPage++;
		}


	}
	painter.end();
}

void ComicBook::nextPage() {
	if (currentPage != backPage) {
		setPageNumber(currentPage + 1 );
		refresh();
	}
	else {
		QMessageBox::critical(
			this,
			tr("ComDrawer"),
			tr("Cannot go past the last page."));
	}
	
}

void ComicBook::prevPage() {
	if (currentPage != 0) {
		setPageNumber(currentPage - 1);
		refresh();
	}
	else {
		QMessageBox::critical(
			this,
			tr("ComDrawer"),
			tr("Cannot go past the first page."));
	}

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
	pagesAct = new QAction(tr("&Jump To Page"), this);
	connect(pagesAct, SIGNAL(triggered()), SLOT(pageSelect()));
	downloadComicAct = new QAction(tr("&Download Comic"), this);
	connect(downloadComicAct, SIGNAL(triggered()), SLOT(downloadComicBook()));
	nextPageAct = new QAction(tr("&Next Page"), this);
	connect(nextPageAct, SIGNAL(triggered()), SLOT(nextPage()));
	prevPageAct = new QAction(tr("&Previous Page"), this);
	connect(prevPageAct, SIGNAL(triggered()), SLOT(prevPage()));
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
	menuBar()->addAction(nextPageAct);
	menuBar()->addAction(prevPageAct);
}

/*
* Reads the configuration text file to place the panels.
*/
void ComicBook::readTextFile()
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
			std::string blankPanel;
			if (panelId == coverPage || panelId == maxPanelCount)
			{
				blankPanel = "blankCoverBackPanel.png";
			}
			else
			{
				blankPanel = "blankPanel.png";
			}
			
			uploadImage(panelId, blankPanel, page);
		}
		if (!sixPanel)
		{
			break;
		}
	}


		
}

/*
* Adds a panel image to the preview window
* 
* @param[in] - panel id - Id of te panel.
* @param[in] - filename - Configuration file name.
* @param[in] - page - layout to add the images to.
*/
void ComicBook::uploadImage(int panel, std::string filename, QGridLayout* page)
{
	QImage panelImage(filename.c_str());
	QLabel* imageLabel = new QLabel();
	QFrame* myHFrame = new QFrame();
	myHFrame->setFrameShape(QFrame::HLine);
	QFrame* myVFrame = new QFrame();
	myVFrame->setFrameShape(QFrame::VLine);
	
	if (panel == coverPage)
	{
		panelImage = panelImage.scaled(_maxWidth, _maxHeight, Qt::KeepAspectRatioByExpanding);
		imageLabel->setPixmap(QPixmap::fromImage(panelImage));
		imageLabel->setMaximumHeight(_maxHeight);
		imageLabel->setMaximumWidth(_maxWidth);
		page->addWidget(imageLabel, 0, 0, 3, 2);
	}
	else if (panel == maxPanelCount)
	{
		panelImage = panelImage.scaled(_maxWidth, _maxHeight, Qt::KeepAspectRatioByExpanding);
		imageLabel->setPixmap(QPixmap::fromImage(panelImage));
		imageLabel->setMaximumHeight(_maxHeight);
		imageLabel->setMaximumWidth(_maxWidth);
		page->addWidget(imageLabel, 0, 0, 3, 2);
	}
	else
	{
		panelImage = panelImage.scaled(_panelWidth, _panelHeight, Qt::IgnoreAspectRatio);
		imageLabel->setPixmap(QPixmap::fromImage(panelImage));
		page->addWidget(myVFrame, 0, 1, 3, 3);
		
		int panelKey = panel;
		if (panel > 6)
		{
			panelKey = panel - (6 * (currentPage - 1));
		}
		
 		if (panelKey == 1)
		{
			page->addWidget(myHFrame, 0, 0, 2, 2);
			page->addWidget(imageLabel, 0, 0, 1, 1);		
			
		}
		else if (panelKey == 2)
		{
			page->addWidget(imageLabel, 0, 1, 1, 1);
			
		}
		else if (panelKey == 3)
		{
			page->addWidget(imageLabel, 1, 0, 1, 1);
			page->addWidget(myHFrame, 1, 0,2, 2);
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

/*
* Updates the current page number.
*/
void ComicBook::setPageNumber(int newPage)
{
	currentPage = newPage;
}

/*
* Creates the comic book structure. 
*/
void ComicBook::createComicBook()
{
	bool status;
	QString text = QInputDialog::getText(this, tr("ComDrawer - Create Comic"), tr("Enter Comic Book name."),QLineEdit::Normal,tr(""),&status);
	if (status && !text.isEmpty())
	{
		std::string dir = text.toStdString();
		dir.erase(std::remove_if(dir.begin(), dir.end(), ::isspace), dir.end());
#ifdef _WIN32
		if (_mkdir(dir.c_str()) == -1)
		{
			QMessageBox::critical(
				this,
				tr("ComDrawer"),
				tr("Comic Book Creation Failed: Directory could not be created."));
			return;
		}
#else
		if (mkdir(dir.c_str()) == -1)
		{
			QMessageBox::critical(
				this,
				tr("ComDrawer"),
				tr("Comic Book Creation Failed: Directory could not be created."));
			return;
		}

#endif // _WIN32


		
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

/*
* Returns the Active comic book name
*/
QString ComicBook::getActiveComicBook()
{
	return _activeComicBook;
}

/*
* Opens the comic book file.
*/
void ComicBook::openComicBook()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open File"), QDir::currentPath());
	
	if (fileName.isEmpty())
	{
		return;
	}
	std::string strFileName = fileName.toStdString();
	if (strFileName.find("_proj.txt") == std::string::npos)
	{
		return;
	}

	_activeComicBookConfigurationFile = strFileName;

	std::ifstream fin;
	fin.open(_activeComicBookConfigurationFile);

	if (fin.fail())
	{
		QMessageBox::critical(
			this,
			tr("ComDrawer"),
			tr("Failed to open project file."));
		return;
	}
	std::string comicNameHeader = "Comic Book Name:";
	std::string comicPageCountHeader = "Comic Book Page Count:";
	std::string pgCount;

	while (!fin.eof())
	{
		std::string temp = "";

		getline(fin, temp);
		auto t = temp.find(comicNameHeader) != std::string::npos;

		if (t)
		{
			_activeComicBook = QString::fromStdString(temp.substr(comicNameHeader.size(), temp.size() - 1));

		}
		else
		{
			break;
		}

		getline(fin, temp);
		t = temp.find(comicPageCountHeader) != std::string::npos;

		if (t)
		{
			try
			{
				pgCount = temp.substr(comicPageCountHeader.size(), temp.size() - 1);
				pageCount = stoi(pgCount);
				backPage = pageCount-1;
				maxPanelCount = ((pageCount - 2) * 6) + 1;

			}
			catch (int num)
			{
				break;
			}

		}
	
		break;


		
	}
	fin.close();
}
/*
* Gets the configuration filename for the project.
*/
std::string ComicBook::getActiveComicBookConfigurationFile()
{
	return _activeComicBookConfigurationFile;
}

/*
* Removes a given entry.
* 
* @returns - True if the entry was removed.
*/
bool ComicBook::removeEntry()
{
	bool status = false;
	std::ifstream fin;
	std::ofstream fout;
	int count = 6;
	int id;

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
			id = temp.find(search);
			if (id != std::string::npos)
			{
				temp.replace(id, search.length(), "");
			}
			else
			{
				temp = temp + "\n";
			}
			fout.write(temp.c_str(), temp.size());

		}
		fin.close();
		fout.close();
		remove(_activeComicBookConfigurationFile.c_str());
		status = rename("temp.txt", _activeComicBookConfigurationFile.c_str());
	}


	return status;
}

/*
* Modifes the configuration file.
* 
* @param[in] - entryToChange - String name to change.
* @param[in] - replacementText - String value of new string.
*/
void ComicBook::modifyConfigurationFile(std::string entryToChange, std::string replacementText)
{
	bool status = false;
	std::ifstream fin;
	std::ofstream fout;
	std::string search = entryToChange;
	std::string temp = "";
	bool found = false;

	fin.open(_activeComicBookConfigurationFile);

	if (fin.fail())
	{
		return;
	}

	fout.open("temp.txt");

	if (fout.fail())
	{
		return;
	}
	status = true;
	while (getline(fin, temp))
	{
		int id = temp.find(search);
		int size = temp.length();
		if (id != std::string::npos)
		{
			temp.replace(id, size, replacementText);
		}
		else
		{
			temp = temp + "\n";
		}
		fout.write(temp.c_str(), temp.size());

	}

	fin.close();
	fout.close();
	remove(_activeComicBookConfigurationFile.c_str());
	status = rename("temp.txt", _activeComicBookConfigurationFile.c_str());
		
}


/*
* Updates page number in the configuration file.
*/
void ComicBook::updatePageNumber()
{
	std::string comicPageCountHeader = "Comic Book Page Count:";
	std::string replacement = comicPageCountHeader +  std::to_string(pageCount)+"\n";
	
	modifyConfigurationFile(comicPageCountHeader, replacement);
}

/*
* Handles resize events.
* @params[in] - event - resize  event.
*/
void ComicBook::resizeEvent(QResizeEvent* event)
{
	//refresh();
	QWidget::resizeEvent(event);
}