#include "../Header/ComDrawerCommand.h"

ComDrawerCommand::ComDrawerCommand(QImage image,QString textChange, QUndoCommand* parent)
    : QUndoCommand(parent)
{
    _undoImage = image;    
    setText(QObject::tr("%1").arg(textChange));
}


ComDrawerCommand::~ComDrawerCommand()
{
}

void ComDrawerCommand::undo()
{ 
    auto cv = CanvasView::getInstance();
    _redoImage = cv->getImage();
    cv->setImage(_undoImage);
}

void ComDrawerCommand::redo()
{
    auto cv = CanvasView::getInstance();
    if (!_redoImage.isNull())
    {
        _undoImage = cv->getImage();
        cv->setImage(_redoImage);
    }
}
