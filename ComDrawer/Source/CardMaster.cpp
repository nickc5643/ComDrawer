#include "../Header/CardMaster.h"

CardMaster::CardMaster()
{
	_cardTitle.clear();
    _cardDesp.clear();
    _cardList.clear();
	_cardFilename.clear();
	_cardCount = 0;

	createActions();
	createMenus();
	ui.setupUi(this);
	setWindowTitle(tr("ComDrawer - Card List Preview"));
	_cardDisplayArea = new QWidget();

	_maxWidth = 1800;
	_maxHeight = 900;

}

void CardMaster::createActions()
{

}
void CardMaster::createMenus()
{

}
void CardMaster::readTextFile()
{

}

void CardMaster::createCardList()
{
    bool status;
    QString text = QInputDialog::getText(this, tr("ComDrawer - Create Card List"), tr("Enter List name."), QLineEdit::Normal, tr(""), &status);
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
	#endif

		std::ofstream fin;
		_activeCardList = text;
		_activeCardConfigurationFile = dir + "/" + _activeCardList.toStdString() + "_proj.txt";
		fin.open(_activeCardConfigurationFile);

		if (fin.fail())
		{
			QMessageBox::critical(
				this,
				tr("ComDrawer"),
				tr("Card List Creation Failed: Failed to create project configuration file"));
			return;
		}
		std::string cardListNameHeader = "Card List Name:" + _activeCardList.toStdString() + "\n";
		std::string cardNumberCount = "Number of Cards:" + std::to_string(++_cardCount) + "\n";
		fin.write(cardListNameHeader.c_str(), cardListNameHeader.size());
		fin.write(cardNumberCount.c_str(), cardNumberCount.size());
		fin.close();
    }
}

void CardMaster::setCardTitle()
{
	_cardTitle;
}

void CardMaster::setCardDescription()
{
	if (_cardTitle == "")
	{
		return;
	}

}

/*
* Refreshes the preview window.
*/
void CardMaster::refresh()
{
	delete _cardDisplayArea;
	_cardDisplayArea = new QWidget();
	_cardDisplayArea->resize(_maxWidth, _maxHeight);
	readTextFile();
}