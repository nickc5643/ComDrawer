#include "CanvasView.h"
#include <QtWidgets>
#include <QMainWindow>
#include <string>
/*
  Class constructor
*/
CanvasView::CanvasView(QWidget* parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    _isDrawing = false;
    _isModified = false;
    _pencilWidth = 1;
    _eraserWidth = 1;
    _paintWidth = 1;
    _maxPanel = 20;
    _textboxWidth = 12;
    _pencilColor = Qt::gray;
    _eraserColor = Qt::white;
    _paintColor = Qt::black;
    _workingTool = pencil;

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
    default:
        break;
    }

}

/* End Getters and Setters */
/****************************/

/*
* Sets the color for the correct tool.
*/
void CanvasView::setColor()
{
    if (_workingTool == paint)
    {
        QColor newColor = QColorDialog::getColor(penColor());
        if (!newColor.isValid())
        {
            QMessageBox::critical(this, tr("ComDrawer"), tr("<p> Selected color was not valid.</p>"));
            return;
        }
        setPaintColor(newColor);
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
            1, 50, 1, &ok);
        if (ok)
            setPaintWidth(newWidth);
    }
    else if (getworkingTool() == eraser)
    {
        newWidth = QInputDialog::getInt(this, tr("ComDrawer"),
            tr("Select eraser width:"),
            getEraserWidth(),
            1, 50, 1, &ok);
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
    if (event->button() == Qt::LeftButton)
    {
        _lastKnownPoint = event->pos();
        _isDrawing = true;
       
    }
}

/*
* Handles mouse move events.
* @params[in] - event - mouse event.
*/
void CanvasView::mouseMoveEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::LeftButton) && _isDrawing)
    {
        if (_workingTool != element)
        {          
            drawLineTo(event->pos());
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
        if (_workingTool == element)
        {
            placeElement(event->x(), event->y());
        }
        else if (_workingTool == textbox)
        {
            placeText(event->x(), event->y());
        }
        else
        {
            drawLineTo(event->pos());
        }
        
        _isDrawing = false;
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

   QPixmap scaledElement = elementToPlace.scaled(elementToPlace.width(), elementToPlace.height());
   QPainter painter(&_image);
   painter.drawPixmap(x, y, scaledElement.width(), scaledElement.height(), scaledElement);
   painter.end();
   update();
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
    newImage.fill(qRgb(255, 255, 255));
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
        _image.fill(qRgb(255, 255, 255));
        update();
        _isModified = false;
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
    _image.fill(qRgb(255, 255, 255));
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

    QImage elementImage = _image;
    resizeImage(&elementImage, size());


    if (elementImage.save(filename))
    {
        _isModified = false;
    }

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

