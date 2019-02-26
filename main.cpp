#include <QGuiApplication>
#include "window/rasterwindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    RasterWindow window;
    window.show();

    return a.exec();
}
