#pragma once

#include <QtWidgets/QWidget>
#include <QList>
#include <QImage>
#include <QPoint>
#include <QColor>
#include <string>
#include <iostream>
#include <fstream>

/*
* The purpose of this class is to control the Canvas widget.
*/
class CanvasView : public QWidget
{
	Q_OBJECT

public:
	enum drawingTool
	{
		pencil = 0,
		paint = 1,
		eraser = 2,
		fillCan = 3,
		straightLine = 4,
		textbox = 5,
		element = 6
	};
	CanvasView(QWidget* parent = nullptr);
	~CanvasView();
	void setPencilWidth(int width);
	int getPencilWidth() const { return pencilWidth; };
	int getEraserWidth() { return eraserWidth; };;
	drawingTool getworkingTool() { return _workingTool;};
	QColor penColor() const { return paintColor; }
	int penWidth() const { return paintWidth; }
	void setWorkingToolSelection(int selection);
	void setPaintWidth(int width);
	void setPaintColor(const QColor &color);
	void setEraserWidth(int width);
	void setColor();
	void setWidth();
	void clearActiveScreen();
	bool setPanel(std::string comicBookConfigFile);
	void setMaxPanel(int newMaxPanel);
	bool saveMyPanel();
	QString saveAs();
	bool openPanel();
	void newPanel();
	void selectDefaultElement();
	void selectCustomElement();
	void saveElement();
	

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event)override;
	
	

private:
	void drawLineTo(const QPoint& endPoint);
	void fillArea(const QPoint& endPoint);
	void resizeImage(QImage* image, const QSize& newSize);
	bool openImage(const QString& fileName);
	void modifyConfigurationFile(std::string entryToChange, std::string replacementText);
	void removeEntry(int id);
	bool savePanel(const QString& fileName);
	void writeToFile(const QString& fileName, int panelId, std::string comicBookConfigFile);
	bool validatePanel(int id);
	bool checkExists(int panelId);
	void placeElement(int x, int y);

	int pencilWidth;
	int eraserWidth;
	int paintWidth;
	bool isDrawing;
	bool isModififed;
	QColor pencilColor;
	QColor eraserColor;
	QColor paintColor;
	QImage image;
	QPoint lastKnownPoint;
	drawingTool _workingTool;
	int maxPanel;
	QString _panelName;
	QString _ElementName;
	std::string _activeComicBookConfigurationFile;
	QString _elementPlacer;
	

};

