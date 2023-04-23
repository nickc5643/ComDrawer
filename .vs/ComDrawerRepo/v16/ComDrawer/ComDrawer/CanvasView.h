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
		textbox = 3,
		element = 4
	};
	CanvasView(QWidget* parent = nullptr);
	~CanvasView();
	void setPencilWidth(int width);
	int getPencilWidth() const { return _pencilWidth; };
	int getEraserWidth() { return _eraserWidth; };;
	drawingTool getworkingTool() { return _workingTool;};
	QColor penColor() const { return _paintColor; }
	int penWidth() const { return _paintWidth; }
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
	int getTextBoxWidth();
	void setTextBoxWidth(int newWidth);
	

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event)override;
	
	

private:
	void drawLineTo(const QPoint& endPoint);
	void resizeImage(QImage* _image, const QSize& newSize);
	bool openImage(const QString& fileName);
	void modifyConfigurationFile(std::string entryToChange, std::string replacementText);
	void removeEntry(int id);
	bool savePanel(const QString& fileName);
	void writeToFile(const QString& fileName, int panelId, std::string comicBookConfigFile);
	bool validatePanel(int id);
	bool checkExists(int panelId);
	void placeElement(int x, int y);
	void placeText(int x, int y);

	int _pencilWidth;
	int _eraserWidth;
	int _paintWidth;
	int _textboxWidth;
	bool _isDrawing;
	bool _isModified;
	QColor _pencilColor;
	QColor _eraserColor;
	QColor _paintColor;
	QImage _image;
	QPoint _lastKnownPoint;
	drawingTool _workingTool;
	int _maxPanel;
	QString _panelName;
	QString _ElementName;
	std::string _activeComicBookConfigurationFile;
	QString _elementPlacer;
	

};

