#pragma once
#include <QtWidgets/QWidget>
#include <QColor>
#include <QPainter>
#include <QLabel>
#include <QRubberBand>
#include <QPalette>
#include <QImage>
#include <QMainWindow>
#include "ui_ElementPreview.h"
#include <QGridLayout>
#include <QMenuBar>
#include <QAction>
#include <QMenuBar>
#include <QSizeGrip>
#include <QPaintEvent>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPixmap>

//

/*
* 
*/
class ElementPreview : public QMainWindow
{
	Q_OBJECT

public:

	ElementPreview(QWidget* parent = nullptr);
	~ElementPreview();
	void elementPreviewDisplay(QImage image);
	void elementPreviewHide();

protected:
	void resizeEvent(QResizeEvent* event)override;
	void paintEvent(QPaintEvent* event)override;

private slots:
	void finishChanges();
	void removeWhiteSpace();
	void modifiyElementSize();

private:
	void createActions();
	void createMenus();
	void modifyCustomElement(int width, int height);
	void refresh();
	void resizeImage(QImage* image, const QSize& newSize);
	
	
	QLabel* _previewDisplay;
	QRubberBand *_rubberBand;
	Ui::ElementName ui;
	QWidget* _window;
	QAction* _finishAct;
	QAction* _removeWhiteSpaceAct;
	QAction* _resizeAct;
	QImage _image;
	QRgb _cropColor;
};