#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>    
#include <time.h>
#include <iostream>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

class CanvasLogger
{
public:
	CanvasLogger();
	~CanvasLogger();
	void logger(std::string text, bool startingEntry=false);
	QString readLog();
	static CanvasLogger* getInstance();

private:
	std::string _filename;
	std::string getTimeString();
	bool _update;
	QString _currentReadingLine;
};
