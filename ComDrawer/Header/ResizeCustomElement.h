#pragma once
#include <QtWidgets/QWidget>
#include <QLabel>
#include <QImage>
#include <QRubberBand>

/*
* The purpose of this class is to control the Canvas widget.
*/
class ResizeCustomElement : public QWidget
{
	Q_OBJECT

public:
	ResizeCustomElement(QImage image, QWidget* parent = nullptr);
	QImage returnImage();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	QImage _displayImage;
	QRubberBand* _rubberBand;
};