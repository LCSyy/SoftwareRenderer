#include "rasterwindow.h"
#include <QImage>
#include <QPen>
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
     // timer->start(16);
}

RasterWindow::~RasterWindow()
{

}

void RasterWindow::render(QPainter *painter)
{
    _painter = painter;

    // static bool grow = true;
    static float radius = 0.0f;
    static Vector2 vec(100.0f,0.0f);

    Vector2 vec_rotate = vec.rotate(radius);
    vec_rotate += Vector2{200.0f,200.0f};
    draw_point(static_cast<int>(vec_rotate._x),static_cast<int>(vec_rotate._y), Color{1.0f,0.0f,0.0f,1.0f});

    radius += 0.1f;
    if(radius > PI*2.0f)
        radius = 0.0f;

    // if(radius > PI*2.0f) {
    //     grow = false;
    // } else if(radius < 0.0f) {
    //     grow = true;
    // }
    //
    // if(grow) {
    //     radius += 0.1f;
    // } else {
    //     radius -= 0.1f;
    // }

    draw_line_dda(Point2D{vec_rotate._x,vec_rotate._y},Point2D{200.0f,200.0f},Color{1.0f,0.0f,0.0f,1.0f});

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
