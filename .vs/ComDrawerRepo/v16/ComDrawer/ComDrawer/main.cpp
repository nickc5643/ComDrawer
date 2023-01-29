#include "ComDrawer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ComDrawer w;
    w.show();
    return a.exec();
}
