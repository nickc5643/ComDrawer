#pragma once
#include <QUndoCommand>
#include <QImage>
#include "CanvasView.h"
#include "CanvasLogger.h"

class ComDrawerCommand : public QUndoCommand
{
public:
    ComDrawerCommand(QImage image, QString textChange, QUndoCommand* parent = nullptr);
    ~ComDrawerCommand();

    void undo() override;
    void redo() override;

private:
    QImage _undoImage;
    QImage _redoImage;
};

