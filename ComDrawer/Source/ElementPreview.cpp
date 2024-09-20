#include "../Header/ElementPreview.h"
#include "../Header/CanvasView.h"

//Constructors/Destructor 

ElementPreview::ElementPreview(QWidget* parent)
{

    ui.setupUi(this);
    _window = new QWidget();
    createActions();
    createMenus();
    
   setWindowTitle(tr("Custom Element Resize Preview"));

   _previewDisplay = new QLabel();
   _previewDisplay->setScaledContents(true);
   //QHBoxLayout* layout = new QHBoxLayout();
   //layout->addWidget(_previewDisplay, 0,0);
  // _window->setLayout(layout);
   _cropColor = QColor(Qt::white).rgb();
  
}

ElementPreview::~ElementPreview() = default;

// Override Methods

void ElementPreview::resizeEvent(QResizeEvent* event)
{   
    QWidget::resizeEvent(event);
}

/*
* Handles paint events.
* @params[in] - event - Paint event.
*/
void ElementPreview::paintEvent(QPaintEvent* event)                                                         
{
    QPainter painter(this);        
    QRect dirtyRect = event->rect();
    
    //painter.drawImage(dirtyRect, _image, dirtyRect);

    painter.drawPixmap(QPoint(50, 50), QPixmap::fromImage(_image));
}
                                                                                                                                                                       
//Getters and Setters


//Actions/menus/slots



void ElementPreview::finishChanges()
{
    auto cv = CanvasView::getInstance();
    cv->saveUpdatedCustomElement(_image);
}

void ElementPreview::removeWhiteSpace()
{
    QRect croppedRegion(width()/2, height()/2 ,_image.width(), _image.height());
   
    // Top
    for (int row = 0; row < _image.height()-1; row++) {
        for (int col = 1; col < _image.width(); col++) {
            if (_image.pixel(col, row) != _cropColor) {
                croppedRegion.setTop(row);
                row = _image.height();
                break;
            }
        }
    }

    // Bottom
    for (int row = _image.height() - 1; row >= 0; row--) {
        for (int col = 0; col < _image.width(); col++) {
            if (_image.pixel(col, row) != _cropColor) {
                croppedRegion.setBottom(row);
                row = -1;
                break;
            }
        }
    }

    // Left
    for (int col = 0; col < _image.width()-1; col++) {
        for (int row = 1; row < _image.height(); row++) {
            if (_image.pixel(col, row) != _cropColor) {
                croppedRegion.setLeft(col);
                col = _image.width();
                break;
            }
        }
    }

    // Right
    for (int col = _image.width()-1; col >= 0; col--) {
        for (int row = 0; row < _image.height(); row++) {
            if (_image.pixel(col, row) != _cropColor) {
                croppedRegion.setRight(col);
                col = -1;
                break;
            }
        }
    }
    _image = _image.copy(croppedRegion);
   
    update();

}

void ElementPreview::modifiyElementSize()
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

    int newHeight = 0;
    int newWidth = 0;

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
                newHeight = tempInt;
            }
            else
            {
                newWidth = tempInt;
            }
        }
    }

    resizeImage(&_image, QSize(newWidth, newHeight));
}


void ElementPreview::createActions()
{
    _finishAct = new QAction(tr("&Save Element"), this);
    connect(_finishAct, SIGNAL(triggered()), SLOT(finishChanges()));
    _finishAct->setShortcut(tr("ctrl+s"));

    _removeWhiteSpaceAct = new QAction(tr("&Crop Image"), this);
    connect(_removeWhiteSpaceAct, SIGNAL(triggered()), SLOT(removeWhiteSpace()));
    _removeWhiteSpaceAct->setShortcut(tr("ctrl+w"));

    _resizeAct = new QAction(tr("&Resize Image"), this);
    connect(_resizeAct, SIGNAL(triggered()), SLOT(modifiyElementSize()));
    _resizeAct->setShortcut(tr("ctrl+r"));
}
void ElementPreview::createMenus()
{
    menuBar()->addAction(_finishAct);
    menuBar()->addAction(_removeWhiteSpaceAct);
    menuBar()->addAction(_resizeAct);
}

// Other Methods
void ElementPreview::elementPreviewDisplay(QImage image)
{
    _window->resize(image.size());
    _image = image;
    setCentralWidget(_window);
    update();
}

void ElementPreview::elementPreviewHide()
{
    delete _window;
}

void ElementPreview::modifyCustomElement(int width, int height)
{
    QImage tempImage = _image;
    _image = tempImage.scaled(width,height);
}

void ElementPreview::refresh()
{
    _previewDisplay->clear();
    QPixmap pixelMap(QPixmap::fromImage(_image));
    _previewDisplay->setPixmap(pixelMap);
    _previewDisplay->resize(pixelMap.size());
    update();
}

/*
    Resizes the canvas.
    @param[in] - image - QImage
    @param[in] - newSize - QSize

*/
void ElementPreview::resizeImage(QImage* image, const QSize& newSize)
{
    if (image->size() == newSize)
    {
        return;
    }
    
    _image = image->scaled(newSize);
    update();  
}



