#include "window.h"

#include <QApplication>
#include <QPushButton>
// TODO: add resizing

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.show();
    return QApplication::exec();
}