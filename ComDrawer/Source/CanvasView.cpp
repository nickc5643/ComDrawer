#include "../Header/CanvasView.h"
#include <QtWidgets>
#include <QMainWindow>
#include <string>
#include "../Header/ComDrawerCommand.h"
/*
  Class constructor
*/

CanvasView* _cv_instance = nullptr;

CanvasView::CanvasView(QWidget* parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents, Qt::WA_TransparentForMouseEvents);
    setMouseTracking(true);
    _undoStack = new QUndoStack(this);
    _isDrawing = false;
    _isModified = false;
    _pencilWidth = 5;
    _eraserWidth = 10;
    _paintWidth = 10;
    _maxPanel = 20;
    _textboxWidth = 12;
    _pencilColor = Qt::gray;
    _eraserColor = Qt::white;
    _paintColor = Qt::black;
    _workingTool = pencil;
    _canvasLogger = new CanvasLogger();
    _cv_instance = this;
    _elementWidth = -1;
    _elementHeight = -1;
    _previewDisplay = new QLabel(this);
    _drawingToolPreviewDisplay = new QLabel(this);
    _straightLineColor = Qt::black;
    _straightLineWidth = 10;
    _saveCustomElementPreview = new ElementPreview();
    _image.fill(Qt::white);
}


/****************************/
/* Getters and Setters */
/*
* Sets the pencil width.
* @params[in] - width - integer size.
*/
void CanvasView::setPencilWidth(int width)
{
    _pencilWidth = width;
}

/*
* Sets the paintbrush width.
* @params[in] - width - integer size.
*/
void CanvasView::setPaintWidth(int width)
{
    _paintWidth = width;
}

/*
* Sets the paintbrush color.
* @params[in] - color - QColor to change brush to
*/
void CanvasView::setPaintColor(const QColor &color)
{
    _paintColor = color;
}

void CanvasView::setStraightLineWidth(int width)
{
    
    _straightLineWidth = width;

}
void CanvasView::setStraightLineColor(const QColor& color)
{
    _straightLineColor = color;
}

/*
* Sets the eraser width.
* @params[in] - width - integer size.
*/
void CanvasView::setEraserWidth(int width)
{
    _eraserWidth = width;
}

int CanvasView::getTextBoxWidth()
{
    return _textboxWidth;
}
void CanvasView::setTextBoxWidth(int newWidth)
{
    _textboxWidth = newWidth;
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
        _workingTool = pencil;
        break;
    case 1:
        _workingTool = paint;
        break;
    case 2:
        _workingTool = eraser;
        break;
    case 3:
        _workingTool = textbox;
        break;
    case 5:
        _workingTool = straightLine;
    default:
        break;
    }

}

QUndoStack* CanvasView::getUndoStack()
{
    return _undoStack;
}

CanvasView* CanvasView::getInstance()
{
    return _cv_instance;
}

void CanvasView::setImage(QImage updatedImage)
{
    if (updatedImage.size() != size())
    {
        resizeImage(&updatedImage, size());
    }
    _image = updatedImage;
    update();
}

QImage CanvasView::getImage()
{
    return _image;
}

/* End Getters and Setters */
/****************************/

/*
* Sets the color for the correct tool.
*/
void CanvasView::setColor()
{
    if (getworkingTool() == paint)
    {
        QColor newColor = QColorDialog::getColor(penColor());
        if (!newColor.isValid())
        {
            QMessageBox::critical(this, tr("ComDrawer"), tr("<p> Selected color was not valid.</p>"));
            return;
        }
        setPaintColor(newColor);
    }
    else if (getworkingTool() == straightLine)
    {
        QColor newColor = QColorDialog::getColor(penColor());
        if (!newColor.isValid())
        {
            QMessageBox::critical(this, tr("ComDrawer"), tr("<p> Selected color was not valid.</p>"));
            return;
        }
        setStraightLineColor(newColor);
    }
    else
    {
        QMessageBox::critical(this, tr("ComDrawer"), tr("<p> Selected tool does not support color change.</p>"));
    }

}

/*
* Sets the width for the correct tool.
*/
void CanvasView::setWidth()
{
    bool ok;
    int newWidth = 0;
    if (getworkingTool() == paint)
    {
        newWidth = QInputDialog::getInt(this, tr("ComDrawer"),
            tr("Select paint width:"),
            penWidth(),
            1, 100, 1, &ok);
        if (ok)
            setPaintWidth(newWidth);
    }
    else if (getworkingTool() == eraser)
    {
        newWidth = QInputDialog::getInt(this, tr("ComDrawer"),
            tr("Select eraser width:"),
            getEraserWidth(),
            1, 100, 1, &ok);
        if (ok)
            setEraserWidth(newWidth);
    }
    else if (getworkingTool() == textbox)
    {
        newWidth = QInputDialog::getInt(this, tr("ComDrawer"),
            tr("Select Text Font Size:"),
            getTextBoxWidth(),
            1, 100, 1, &ok);
        if (ok)
            setTextBoxWidth(newWidth);
            
    }
    else if (getworkingTool() == straightLine)
    {
        newWidth = QInputDialog::getInt(this, tr("ComDrawer"),
            tr("Select Text Font Size:"),
            _straightLineWidth,
            1, 100, 1, &ok);
        if (ok)
            setStraightLineWidth(newWidth);
    }
    else
    {
        QMessageBox::critical(this, tr("ComDrawer"), tr("<p> Only the paint brush and eraser can change widths.</p>"));
    }
}

/*
* Handles mouse press events.
* @params[in] - event - mouse event.
*/
void CanvasView::mousePressEvent(QMouseEvent* event)
{

    if (_workingTool != element)
    {
        int mouseX = static_cast<int>(event->position().x());
        int mouseY = static_cast<int>(event->position().y());

        drawingToolPreviewDisplay(mouseX, mouseY);
    }
    else
    {
        drawingToolPreviewHide();
    }

    if ((event->buttons() & Qt::LeftButton))
    {
        _lastKnownPoint = event->pos();
        _isDrawing = true;
        if (_workingTool != element)
        {
            QUndoCommand* tmp = new ComDrawerCommand(_image, tr("Added new line"));
            _undoStack->push(tmp);
            
        }
    }
    else if ((event->buttons() & Qt::RightButton) && _workingTool == element)
    {
        int mouseX = static_cast<int>(event->position().x());
        int mouseY = static_cast<int>(event->position().y());
        elementPreviewDisplay(mouseX, mouseY);

    }
}

/*
* Handles mouse move events.
* @params[in] - event - mouse event.
*/
void CanvasView::mouseMoveEvent(QMouseEvent* event)
{
    if (_workingTool != element)
    {
        int mouseX = static_cast<int>(event->position().x());
        int mouseY = static_cast<int>(event->position().y());
        drawingToolPreviewDisplay(mouseX, mouseY);
    }
    else
    {
        drawingToolPreviewHide();
    }

    if (getworkingTool() == straightLine)
    {
        if ((event->button() & Qt::LeftButton) && _isDrawing)
        {
            if (_workingTool != element)
            {
                drawLineTo(event->pos());
            }
        }

    }
    else
    {
        if ((event->buttons() & Qt::LeftButton) && _isDrawing)
        {
            if (_workingTool != element)
            {
                drawLineTo(event->pos());
            }
        }
    }
    


}

/*
* Handles mouse release events.
* @params[in] - event - mouse event.
*/
void CanvasView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && _isDrawing)
    {
        int mouseX = static_cast<int>(event->position().x());
        int mouseY = static_cast<int>(event->position().y());
        if (_workingTool == element)
        {
           placeElement(mouseX, mouseY);
           elementPreviewHide();
        }
        else if (_workingTool == textbox)
        {
            placeText(mouseX, mouseY);
        }
        else
        {
            drawLineTo(event->pos());
        }
        
        _isDrawing = false;
    }
    else if ((event->button() == Qt::RightButton))
    {
        elementPreviewHide();
    }

    if (_workingTool != element)
    {
        int mouseX = static_cast<int>(event->position().x());
        int mouseY = static_cast<int>(event->position().y());
        drawingToolPreviewDisplay(mouseX, mouseY);
    }
    else
    {
        drawingToolPreviewHide();
    }

}

void CanvasView::enterEvent(QEnterEvent* event)
{
    auto m_mousePos = this->mapFromGlobal(QCursor::pos());
    if (_workingTool != element)
    {
        drawingToolPreviewDisplay(m_mousePos.x(), m_mousePos.y());
    }
    else
    {
        drawingToolPreviewHide();
    }
}

void CanvasView::leaveEvent(QEvent* event)
{
}

/*
* Handles paint events.
* @params[in] - event - Paint event.
*/
void CanvasView::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, _image, dirtyRect);

}

/*
* Handles resize events.
* @params[in] - event - resize  event.
*/
void CanvasView::resizeEvent(QResizeEvent* event)
{
    if (width() > _image.width() || height() > _image.height())
    {
        int newWidth = qMax(width() + 128, _image.width());
        int newHeight = qMax(height() + 128, _image.height());
        resizeImage(&_image, QSize(newWidth, newHeight));
        _previewDisplay->resize(newWidth, newHeight);
        _previewDisplay->updateGeometry();
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
    QPainter painter(&_image);
    QColor drawingColor;
    int drawingWidth = 0;
    switch (_workingTool)
    {
    case pencil:
        drawingColor = _pencilColor;
        drawingWidth = _pencilWidth;
        break;
    case paint:
        drawingColor = _paintColor;
        drawingWidth = _paintWidth;
        break;
    case eraser:
        drawingColor = _eraserColor;
        drawingWidth = _eraserWidth;
        break;
    case straightLine:
        drawingColor = _straightLineColor;
        drawingWidth = _straightLineWidth;
    default:
        break;
    }

    if (drawingWidth == 0)
    {
        return;
    }

    
    painter.setPen(QPen(drawingColor, drawingWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(_lastKnownPoint, endPoint);
    int rad = (drawingWidth / 2) + 2;
    update(QRect(_lastKnownPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    _lastKnownPoint = endPoint;

    if (!_isModified)
    {
        _isModified = true;
    }
}

/*
* Places the element on the canvas at a given X and Y point.
* 
* @param[in] x - X coordinate.
* @param[in] y - Y coordinate.
*/
void CanvasView::placeElement(int x, int y)
{
   QPixmap elementToPlace;
   if (!elementToPlace.load(_elementPlacer))
   {
       return;
   }
   
   QUndoCommand* tmp = new ComDrawerCommand(_image, tr("Added Element %1").arg(_elementPlacer));
   _undoStack->push(tmp);

   int width = _elementWidth == -1 ? elementToPlace.width() : _elementWidth;
   int height = _elementHeight == -1 ? elementToPlace.height() : _elementHeight;
   
   QPixmap scaledElement = elementToPlace.scaled(width, height);
   QPainter painter(&_image);
   painter.drawPixmap(x, y, scaledElement.width(), scaledElement.height(), scaledElement);
   painter.end();
   update();
   _canvasLogger->logger("Element Placed.");
   
   
   if (!_isModified)
   {
       _isModified = true;
   }
}

/*
    Resizes the canvas.
    @param[in] - image - QImage
    @param[in] - newSize - QSize

*/
void CanvasView::resizeImage(QImage* _image, const QSize& newSize)
{
    if (_image->size() == newSize)
    {
        return;
    }

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(Qt::white);
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *_image);
    *_image = newImage;
}



/**
* Clears the active screen if there is something to clear.
*/
void CanvasView::clearActiveScreen()
{
    if (!_isModified)
    {
        QMessageBox::critical(this, tr("ComDrawer"), tr("<p>There is nothing to clear.</p>"));
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Clear Design", "Are you sure you want to clear the entire design?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        _image.fill(QColor(Qt::white).rgb());
        update();
        _undoStack->clear();
        _isModified = false;
        _canvasLogger->logger("Screen Cleared.");
        _ElementName.clear();
    }

}

/*
    Class destructor.
*/
CanvasView::~CanvasView()
{

}

/*
* Writes to the project specific file.
* 
* @param[in] - filename - QString filename.
* @param[in] - panelId -  id of the panel.
* @param[in] - comicBookConfigFile - string comic book file name.
*/
void CanvasView::writeToFile(const QString& fileName, int panelId, std::string comicBookConfigFile)
{
    std::string mainPanels = "";
    std::ofstream myfile;
    myfile.open(comicBookConfigFile, std::ios_base::app);
    if (panelId == 0)
    {
        myfile << "panelId=cover" << " " << fileName.toStdString() + "\n";
    }
    else if (panelId == _maxPanel)
    {
        mainPanels = "end";
        myfile << "panelId=end" << " " << fileName.toStdString() + "\n";
    }
    else
    {
        myfile << "panelId=" << panelId << " " << fileName.toStdString() + "\n";
    }
    myfile.close();
}

/*
* Validates the selected Panel value.
* 
* @param[in] - id - panel id.
* 
* @returns - True if the panel is validated.
*/
bool CanvasView::validatePanel(int id)
{
    bool status=true;
    if (id > _maxPanel)
    {
        status = false;
    }
    else if (status && checkExists(id))
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "ComDrawer", "Panel is already set, do you want to replace?",
            QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            status = true;
            removeEntry(id);
        }
        else
        {
            status = false;
        }
    }
    return status;
}


/*
* Sets the image to a panel and stores it in the file.
* 
* @parm[in] - comicBookConfigFile - configuration file for the comicbook.
*/
bool CanvasView::setPanel(std::string comicBookConfigFile)
{
    bool status;
    QString filename = "";
    _activeComicBookConfigurationFile = comicBookConfigFile;
    std::string test = "Select a panel (0 - " + std::to_string(_maxPanel) +")";
    int panelId = QInputDialog::getInt(this, tr("ComDrawer"),
        test.c_str(),
        0,
        0, 212, 0, &status);
    if (status)
        status = validatePanel(panelId);
    else
    {
        return false;
    }
    if (status)
    {
        filename = saveAs();
        status = savePanel(filename);
    }
    if (status)
    {
        writeToFile(filename, panelId, comicBookConfigFile);
    }
    return true;
}

/*
* Saves an image.
* 
* @param[in] - filename to save the image to.
*/
bool CanvasView::savePanel(const QString& fileName)
{
    QImage panelImage = _image;
    resizeImage(&panelImage, size());

    if (panelImage.save(fileName))
    {
        _isModified = false;
        return true;
    }
    return false;
}

/*
* Gives the user a saveas window if the file has not been saved.
* 
* @returns The filename as a QString.
*/
QString CanvasView::saveAs()
{
    QString filename;
    if (_panelName.isEmpty())
    {
        QString initPath = QDir::currentPath() + "/untilted";
        filename = QFileDialog::getSaveFileName(this, tr("Save"), initPath, tr("%1 Files (*%2);;")
            .arg(QString::fromLatin1(".PNG"))
            .arg(QString::fromLatin1(".png")));
        _panelName = filename;
    }
    else
    {
        filename = _panelName;
    }
    return filename;

}

/*
* Saves the panel.
* 
* returns true if the panel is saved correctly.
*/
bool CanvasView::saveMyPanel()
{
    return savePanel(saveAs());
}

/*
* Sets the max panel that can be set.
*/
void CanvasView::setMaxPanel(int newMaxPanel)
{
    _maxPanel = newMaxPanel;
}

/*
* Checks to see if a panel is already set.
* 
* @param[in] - panelId - Integer value of te Id.
* 
* @returns - true if the panel was found, false if not.
*/
bool CanvasView::checkExists(int panelId)
{
    std::ifstream fin;
    bool found = true;
    std::string search = "N/A";
    if (panelId == 0)
    {
        search = "panelId=cover";
    }
    else if (panelId == _maxPanel)
    {
        search = "panelId=end";
    }
    else
    {
        search = "panelId=" + std::to_string(panelId);
    }

    fin.open(_activeComicBookConfigurationFile);
    if (fin.fail())
    {
        return false;
    }
    while (!fin.eof())
    {
        std::string temp = "";
        getline(fin, temp);
        found = temp.find(search) != std::string::npos;
        if (found)
        {
            break;
        }
    }
    fin.close();
    return found;
}

/*
* Opens the panel on the canvas.
* 
* @returns - true if the panel is opened.
*/
bool CanvasView::openPanel()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
        return openImage(fileName);
    return false;
}

void CanvasView::openPNG()
{
    std::string output;
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
    {
        QImage loadedImage;
        if (!loadedImage.load(fileName))
        {
            output = "Failed to load image: " + fileName.toStdString();
        }
        else
        {
            _elementPlacer = fileName;
            _workingTool = element;
            drawingToolPreviewHide();
            output = "Successfully added imgage: " + fileName.toStdString();
        }
    }
    else
    {
       output = "Failed to load image: " + fileName.toStdString();
       
    }
    _canvasLogger->logger(output);
}

/*
* Opens the panel on the canvas.
*
* @param[in] - fileName -  filename of the panel.
* @returns - true if the panel is opened.
*/
bool CanvasView::openImage(const QString& fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;
    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    _image = loadedImage;
    _isModified = false;
    update();
    _panelName = fileName;
    return true;
}

/*
* Creates a new panel
*/
void CanvasView::newPanel()
{
    _panelName = "";
    _ElementName = "";
    _image.fill(QColor(Qt::white).rgb());
    update();
    _isModified = false;
}

/*
* Allows user to select a default element from a list
*/
void CanvasView::selectDefaultElement()
{
    QString selectionCaption = "ComDrawer";
    QString selectionLabel = "Default Element List";
    QDir dir("defaultElements");

    dir.setSorting(QDir::Name);
    QStringList defaultElements = dir.entryList(QDir::AllEntries | QDir::Dirs);

    QString selection = QInputDialog::getItem(this,selectionCaption, selectionLabel, defaultElements);
    _elementPlacer = "defaultElements/"+selection;
    _workingTool = element;
    _elementWidth = -1;
    _elementHeight = -1;
    drawingToolPreviewHide();
}

/*
* Allows the user to select a custom created element.
*/
void CanvasView::selectCustomElement()
{
    QString selectionCaption = "ComDrawer";
    QString selectionLabel = "Custom Elements List";
    QDir dir("customElements/");

    dir.setSorting(QDir::Name);
    QStringList customElements = dir.entryList(QDir::AllEntries | QDir::Dirs);

    QString selection = QInputDialog::getItem(this, selectionCaption, selectionLabel, customElements);
    _elementPlacer = "customElements/"+selection;
    _workingTool = element;
    _elementWidth = -1;
    _elementHeight = -1;
    drawingToolPreviewHide();
}

/*
* Modifes the configuration file.
*
* @param[in] - entryToChange - String name to change.
* @param[in] - replacementText - String value of new string.
*/
void CanvasView::modifyConfigurationFile(std::string entryToChange, std::string replacementText)
{
    bool status = false;
    std::ifstream fin;
    std::ofstream fout;
    std::string search = entryToChange;
    std::string temp = "";
    bool found = false;

    fin.open(_activeComicBookConfigurationFile);

    if (fin.fail())
    {
        return;
    }

    fout.open("temp.txt");

    if (fout.fail())
    {
        return;
    }
    status = true;
    while (getline(fin, temp))
    {
        int id = temp.find(search);
        int size = temp.length();
        if (id != std::string::npos)
        {
            temp.replace(id, size, replacementText);
        }
        else
        {
            temp = temp + "\n";
        }
        fout.write(temp.c_str(), temp.size());

    }

    fin.close();
    fout.close();
    remove(_activeComicBookConfigurationFile.c_str());
    status = rename("temp.txt", _activeComicBookConfigurationFile.c_str());

}

/*
* Removes a panel at a specified Id.
* 
* @param[in] - id - panel id to remove.
*/
void CanvasView::removeEntry(int id)
{
    std::string search;
    if (id == 0)
    {
        search = "panelId=cover";
    }
    else if (id == _maxPanel)
    {
        search = "panelId=end";
    }
    else
    {
        search = "panelId=" + std::to_string(id);
    }
    modifyConfigurationFile(search, "");
}

/*
* Allows the user to save custom elements.
*/
void CanvasView::saveElement()
{
    resizeCustomElement();
}

/*
* Places text in a specific X and Y location on the canvas.
* 
* @param[in] - x - X cooridnate 
* @param[in] - y - Y coordinate
*/
void CanvasView::placeText(int x, int y)
{
    bool ok;

    QString text = QInputDialog::getMultiLineText(this, tr("ComDrawer"), tr("Enter Text:"), "", &ok);

    if (!ok || text.isEmpty())
    {
        return;
    }
    if (!_isModified)
    {
       _isModified = true;
    }
   
    QPainter painter(&_image);
    QFont font;
    font.setPixelSize(_textboxWidth);
    painter.setFont(font);
    
    painter.drawText(x, y, text);
    painter.end();
}

void CanvasView::modifiyElementSize()
{
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Modify Selected Elemnt Height and Width"));

    // Add the lineEdits with their respective labels
    QList<QLineEdit*> fields;

    QLineEdit* lineEdit = new QLineEdit(&dialog);
    QString label = QString("Height");
    form.addRow(label, lineEdit);
    fields << lineEdit;
    
   QLineEdit* lineEdit_w = new QLineEdit(&dialog);
   QString label_w = QString("Width");
   form.addRow(label_w, lineEdit_w);

    fields << lineEdit_w;

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        QString tempQString;
        int tempInt;
        int count = 0;
        foreach(QLineEdit * lineEdit, fields) {

            tempQString = lineEdit->text();
            tempInt = tempQString.split(" ")[0].toInt();
            
            if (count++ == 0)
            {
                _elementHeight = tempInt;
            }
            else
            {
                _elementWidth = tempInt;
            }
        }
    }
}

/**
* @brief Displays a preview of the element to be placed.
* 
* @params[in] x - x cooridnate of mouse.
* @params[in] y - y cooridnate of mouse.
*/
void CanvasView::elementPreviewDisplay(int x, int y)
{
    QPixmap elementToPlace;

    if (!elementToPlace.load(_elementPlacer))
    {
        return;
    }

    int width = _elementWidth == -1 ? elementToPlace.width() : _elementWidth;
    int height = _elementHeight == -1 ? elementToPlace.height() : _elementHeight;

    QPixmap scaledElement = elementToPlace.scaled(width, height);
    
 
    _previewDisplay->setStyleSheet("border-style: solid; border-width:2px; border-color:green;");
    _previewDisplay->setGeometry(QRect(x, y, width, height));
    _previewDisplay->setPixmap(scaledElement);
    _previewDisplay->raise();
    _previewDisplay->update();
    _previewDisplay->show();
}

/**
*@brief hides the element preview.
*/
void CanvasView::elementPreviewHide()
{
    _previewDisplay->hide();
}

void CanvasView::drawingToolPreviewDisplay(int x, int y)
{
    int drawingWidth = 0;
    QPixmap workingToolBrush;

    switch (_workingTool)
    {
    case pencil:
        drawingWidth = _pencilWidth;
        break;
    case paint:
        drawingWidth = _paintWidth;
        break;
    case eraser:
        drawingWidth = _eraserWidth;
        break;
    case straightLine:
        drawingWidth = _straightLineWidth;
        break;
    case textbox:
        drawingWidth = _textboxWidth;
        break;
    default:
        break;
    }

    if (drawingWidth == 0)
    {
        return;
    }

   /*  
    QColor drawingColor;
    QPainter painter(&workingToolBrush);
    painter.setBrush(QBrush(drawingColor));
    painter.drawEllipse(x, y, drawingWidth, drawingWidth);
    painter.end();*/

    int previewX = x - (drawingWidth / 2);
    int previewY = y - (drawingWidth / 2);
    _drawingToolPreviewDisplay->setStyleSheet("border-style: solid; border-width:2px; border-color:black;");
    _drawingToolPreviewDisplay->setPixmap(workingToolBrush);
    _drawingToolPreviewDisplay->setGeometry(QRect(previewX, previewY, drawingWidth, drawingWidth));
    _drawingToolPreviewDisplay->raise();
    _drawingToolPreviewDisplay->update();
    _drawingToolPreviewDisplay->show();
}
void CanvasView::drawingToolPreviewHide()
{
    _drawingToolPreviewDisplay->hide();
}

void CanvasView::resizeCustomElement()
{
    _saveCustomElementPreview->elementPreviewDisplay(_image);
    _saveCustomElementPreview->show();
}

void CanvasView::saveUpdatedCustomElement(QImage newImage)
{

    QString filename;
    if (_ElementName.isEmpty())
    {
        QString initPath = QDir::currentPath() + "/customElements/untilted";
        filename = QFileDialog::getSaveFileName(this, tr("Save"), initPath, tr("%1 Files (*%2);;")
            .arg(QString::fromLatin1(".PNG"))
            .arg(QString::fromLatin1(".png")));
        _ElementName = filename;
    }
    else
    {
        filename = _ElementName;
    }

    if (newImage.save(filename))
    {
        _undoStack->clear();
        _isModified = false;
    }
}