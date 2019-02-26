#include "rasterwindow.h"
#include <QImage>
#include <QPainter>
#include <QTimer>
#include <cmath>
#include <chrono>

#include <QDebug>

#include "math/vector2.h"

RasterWindow::RasterWindow(QWindow *parent)
    : BaseRasterWindow(parent)
{
     QTimer *timer = new QTimer(this);
     connect(timer,SIGNAL(timeout()),this,SLOT(renderNow()));
     timer->start(16);
}

RasterWindow::~RasterWindow()
{

}

void RasterWindow::render(QPainter *painter)
{
    _painter = painter;

    Vector2 vec = Vector2::unit();
    qDebug() << vec.length();

    draw_point(10,10,Color{1.0f,0.0f,0.0f,1.0f});
    _painter = nullptr;
}

void RasterWindow::draw_point(int x, int y, const Color &color)
{
    if(_painter) {
        _painter->setPen(QColor::fromRgbF(static_cast<double>(color.r),
                                          static_cast<double>(color.g),
                                          static_cast<double>(color.b),
                                          static_cast<double>(color.a)));

        _painter->drawPoint(x,y);
    }
}
