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
    isDrawing = false;
    isModififed = false;
    pencilWidth = 1;
    eraserWidth = 1;
    paintWidth = 1;
    maxPanel = 20;
    pencilColor = Qt::gray;
    eraserColor = Qt::white;
    paintColor = Qt::black;
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
    pencilWidth = width;
}

/*
* Sets the paintbrush width.
* @params[in] - width - integer size.
*/
void CanvasView::setPaintWidth(int width)
{
    paintWidth = width;
}

/*
* Sets the paintbrush color.
* @params[in] - color - QColor to change brush to
*/
void CanvasView::setPaintColor(const QColor &color)
{
    paintColor = color;
}

/*
* Sets the eraser width.
* @params[in] - width - integer size.
*/
void CanvasView::setEraserWidth(int width)
{
    eraserWidth = width;
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
    if (event->button() == Qt::LeftButton && isDrawing)
    {
        if (_workingTool != element)
        {
            drawLineTo(event->pos());
        }
        else
        {
            placeElement(event->x(), event->y());
        }
        
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
    switch (_workingTool)
    {
    case pencil:
        drawingColor = pencilColor;
        drawingWidth = pencilWidth;
        break;
    case paint:
        drawingColor = paintColor;
        drawingWidth = paintWidth;
        break;
    case eraser:
        drawingColor = eraserColor;
        drawingWidth = eraserWidth;
        break;
    default:
        break;
    }

    if (drawingWidth == 0)
    {
        return;
    }

    painter.setPen(QPen(drawingColor, drawingWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastKnownPoint, endPoint);
    int rad = (drawingWidth / 2) + 2;
    update(QRect(lastKnownPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastKnownPoint = endPoint;

    if (!isModififed)
    {
        isModififed = true;
    }
}

void CanvasView::placeElement(int x, int y)
{
   QPixmap elementToPlace;
   if (!elementToPlace.load(_elementPlacer))
   {
       return;
   }

   QPixmap scaledElement = elementToPlace.scaled(elementToPlace.width(), elementToPlace.height());
   QPainter painter(&image);
   painter.drawPixmap(x, y, scaledElement.width(), scaledElement.height(), scaledElement);
   painter.end();
   update();
   if (!isModififed)
   {
       isModififed = true;
   }
}

/*
* Does nothing at the moment.
*/
void CanvasView::fillArea(const QPoint& endPoint)
{

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
        _workingTool = pencil;
        break;
    case 1:
        _workingTool = paint;
        break;
    case 2:
        _workingTool = eraser;
        break;
    case 3:
        _workingTool = fillCan;
        break;
    case 4:
        _workingTool = straightLine;
        break;
    default:
        break;
    }
  
}

/**
* Clears the active screen if there is something to clear.
*/
void CanvasView::clearActiveScreen()
{
    if (!isModififed)
    {
        QMessageBox::critical(this, tr("ComDrawer"), tr("<p>There is nothing to clear.</p>"));
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Clear Design", "Are you sure you want to clear the entire design?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        image.fill(qRgb(255, 255, 255));
        update();
        isModififed = false;
    }

}

/*
    Class destructor.
*/
CanvasView::~CanvasView()
{

}

void CanvasView::writeToFile(const QString& fileName, int panelId, std::string comicBookConfigFile)
{
    std::string mainPanels = "";
    std::ofstream myfile;
    myfile.open(comicBookConfigFile, std::ios_base::app);
    if (panelId == 0)
    {
        myfile << "panelId=cover" << " " << fileName.toStdString() + "\n";
    }
    else if (panelId == maxPanel)
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
bool CanvasView::validatePanel(int id)
{
    bool status=true;
    if (id > maxPanel)
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


bool CanvasView::setPanel(std::string comicBookConfigFile)
{
    bool status;
    QString filename = "";
    _activeComicBookConfigurationFile = comicBookConfigFile;
    std::string test = "Select a panel (0 - " + std::to_string(maxPanel) +")";
    int panelId = QInputDialog::getInt(this, tr("ComDrawer"),
        test.c_str(),
        0,
        0, 212, 0, &status);
    if (status)
        status = validatePanel(panelId);
    else
    {
        //error message
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

bool CanvasView::savePanel(const QString& fileName)
{
    QImage panelImage = image;
    resizeImage(&panelImage, size());

    if (panelImage.save(fileName))
    {
        isModififed = false;
        return true;
    }
    return false;
}

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

bool CanvasView::saveMyPanel()
{
    return savePanel(saveAs());
}

void CanvasView::setMaxPanel(int newMaxPanel)
{
    maxPanel = newMaxPanel;
}

bool CanvasView::checkExists(int panelId)
{
    std::ifstream fin;
    bool found = true;
    std::string search = "N/A";
    if (panelId == 0)
    {
        search = "panelId=cover";
    }
    else if (panelId == maxPanel)
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

bool CanvasView::openPanel()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
        return openImage(fileName);
    return false;
}

bool CanvasView::openImage(const QString& fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;
    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    isModififed = false;
    update();
    _panelName = fileName;
    return true;
}

void CanvasView::newPanel()
{
    _panelName = "";
    image.fill(qRgb(255, 255, 255));
    update();
    isModififed = false;
}

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

void CanvasView::removeEntry(int id)
{
    std::string search;
    if (id == 0)
    {
        search = "panelId=cover";
    }
    else if (id == maxPanel)
    {
        search = "panelId=end";
    }
    else
    {
        search = "panelId=" + std::to_string(id);
    }
    modifyConfigurationFile(search, "");
}

void CanvasView::saveElement()
{
    QString filename;
    if (_ElementName.isEmpty())
    {
        QString initPath = QDir::currentPath() + "customElements/untilted";
        filename = QFileDialog::getSaveFileName(this, tr("Save"), initPath, tr("%1 Files (*%2);;")
            .arg(QString::fromLatin1(".PNG"))
            .arg(QString::fromLatin1(".png")));
        _ElementName = filename;
    }
    else
    {
        filename = _ElementName;
    }

    QImage elementImage = image;
    resizeImage(&elementImage, size());


    if (elementImage.save(filename))
    {
        isModififed = false;
    }

}