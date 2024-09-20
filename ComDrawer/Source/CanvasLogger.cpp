#include "../Header/CanvasLogger.h"
#include <stdio.h>

CanvasLogger* _cl_instance = nullptr;

CanvasLogger::CanvasLogger()
{
	if (!_cl_instance)
	{
		_filename = "CanvasViewLog.txt";
		logger("====== Canvas View Logger Start ======", true);
		_cl_instance = this;
	}
	_update = false;
	_currentReadingLine = "";
}

CanvasLogger::~CanvasLogger()
{
}

void CanvasLogger::logger(std::string text, bool startingEntry)
{
	std::ofstream logFile;
	if (startingEntry)
	{
		logFile.open(_filename, std::ios::out | std::ios::trunc);

	}
	else 
	{
		logFile.open(_filename, std::ios::out | std::ios::app);
	}
	
	logFile << "(" << getTimeString() << ") " << text << "\n";
	logFile.close();
	_update = true;
}

std::string CanvasLogger::getTimeString()
{
	/*struct tm tm;
	auto time = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(time);
	std::string uneditedTimeString = std::ctime(&currentTime);
	std::string editedTimeString = uneditedTimeString.erase(uneditedTimeString.length() - 1);
	return editedTimeString;*/
	return "";
}

CanvasLogger* CanvasLogger::getInstance()
{
	return _cl_instance;
}

QString CanvasLogger::readLog()
{
	QFile file(QString::fromStdString(_filename));
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "error", file.errorString());
		return "";
	}

	QTextStream in(&file);
	QString line = "";
	while (!in.atEnd()) {
		line += in.readLine();
		line += "\n";
	}
	
	file.close();
	
	return line;
}