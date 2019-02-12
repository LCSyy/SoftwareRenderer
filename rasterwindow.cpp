#include "rasterwindow.h"
#include <QImage>
#include <QPainter>

RasterWindow::RasterWindow(QWindow *parent)
    : BaseRasterWindow(parent)
{
}

RasterWindow::~RasterWindow()
{

}

void RasterWindow::render(QPainter *painter)
{
    painter->drawPoint(QPointF(100,10));
}
