#include "CanvasView.h"
#include <QtWidgets>
#include <QMainWindow>
/*
  Class constructor
*/
CanvasView::CanvasView(QWidget* parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    isDrawing = false;
    pencilWidth = 1;
    eraserWidth = 1;
    pencilColor = Qt::gray;
    eraserColor = Qt::white;
    
    workingTool = pencil;

}

/*
* Sets the pencil width.
* @params[in] - event - mouse event.
*/
void CanvasView::setPencilWidth(int width)
{
    pencilWidth = width;
}

/*
* Handles mouse press events.
* @params[in] - event - mouse event.
*/
void CanvasView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        lastKnownPoint = event->pos();
        isDrawing = true;
       
    }
}

/*
* Handles mouse move events.
* @params[in] - event - mouse event.
*/
void CanvasView::mouseMoveEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::LeftButton) && isDrawing)
    {
        drawLineTo(event->pos());
    }

}

/*
* Handles mouse release events.
* @params[in] - event - mouse event.
*/
void CanvasView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && isDrawing)
    {
        drawLineTo(event->pos());
        isDrawing = false;
    }

}

/*
* Handles paint events.
* @params[in] - event - Paint event.
*/
void CanvasView::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);

}

/*
* Handles resize events.
* @params[in] - event - resize  event.
*/
void CanvasView::resizeEvent(QResizeEvent* event)
{
    if (width() > image.width() || height() > image.height())
    {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

/*
    Draws a line from one point to the other.
    @params[in] - endPoint - The end draw location.
*/
void CanvasView::drawLineTo(const QPoint& endPoint)
{
    QPainter painter(&image);
    QColor drawingColor;
    int drawingWidth = 0;
    switch (workingTool)
    {
    case pencil:
        drawingColor = pencilColor;
        drawingWidth = pencilWidth;
        break;
    case eraser:
        drawingColor = eraserColor;
        drawingWidth = eraserWidth;
        break;
    default:
        break;
    }

    painter.setPen(QPen(drawingColor, drawingWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastKnownPoint, endPoint);
    int rad = (drawingWidth / 2) + 2;
    update(QRect(lastKnownPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastKnownPoint = endPoint;
}

/*
    Resizes the canvas.
    @param[in] - image - QImage
    @param[in] - newSize - QSize

*/

void CanvasView::resizeImage(QImage* image, const QSize& newSize)
{
    if (image->size() == newSize)
    {
        return;
    }

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

/*
* Sets the design tool the user wants to use.
* @param[in] - selection - interger that references a certain item.
*/
void CanvasView::setWorkingToolSelection(int selection)
{
    switch (selection)
    {
    case 0:
        workingTool = pencil;
        break;
    case 2:
        workingTool = eraser;
        break;
    default:
        break;
    }
  
}

/*
    Class destructor.
*/
CanvasView::~CanvasView()
{

}
