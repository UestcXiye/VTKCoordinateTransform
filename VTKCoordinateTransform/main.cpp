#include "VTKCoordinateTransform.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VTKCoordinateTransform w;
    w.show();
    return a.exec();
}
