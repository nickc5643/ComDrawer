#pragma once

#include <QtWidgets/QWidget>
#include <QList>
#include <QImage>
#include <QPoint>
#include <QColor>

/*
* The purpose of this class is to control the Canvas widget.
*/
class CanvasView : public QWidget
{
	Q_OBJECT

public:
	CanvasView(QWidget* parent = nullptr);
	~CanvasView();
	void setPencilWidth(int width);
	int getPencilWidth() const { return pencilWidth; }
	void setWorkingToolSelection(int selection);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event)override;


private:
	enum drawingTool
	{
		pencil = 0,
		paint = 1,
		eraser = 2,
		fillCan = 3
	};
	void drawLineTo(const QPoint& endPoint);
	void resizeImage(QImage* image, const QSize& newSize);
	int pencilWidth;
	int eraserWidth;
	bool isDrawing;
	QColor pencilColor;
	QColor eraserColor;

	QImage image;
	QPoint lastKnownPoint;
	drawingTool workingTool;

};
