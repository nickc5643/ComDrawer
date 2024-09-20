#include "../Header/ResizeCustomElement.h"

ResizeCustomElement::ResizeCustomElement(QImage image, QWidget* parent)
    : QWidget(parent)
{
    _displayImage = image;
}

void ResizeCustomElement::mousePressEvent(QMouseEvent* event)
{
}

void ResizeCustomElement::mouseMoveEvent(QMouseEvent* event)
{

}


void ResizeCustomElement::mouseReleaseEvent(QMouseEvent* event)
{

}

QImage ResizeCustomElement::returnImage()
{
    return _displayImage;
}