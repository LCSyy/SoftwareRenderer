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
     timer->start(16);
}

RasterWindow::~RasterWindow()
{

}

void RasterWindow::render(QPainter *painter)
{
    _painter = painter;

    static float radius = 0.0f;
    static Vector2 vec(100.0f,0.0f);

    Vector2 vec_rotate = vec.rotate(radius);
    vec_rotate += Vector2{200.0f,200.0f};

    radius += 0.1f;
    if(radius > PI*2.0f)
        radius = 0.0f;

    draw_line_dda(Point2D{vec_rotate._x,vec_rotate._y},Point2D{400.0f,200.0f},Color{0.0f,0.0f,1.0f,1.0f});
    draw_line_bresenham(Point2D{vec_rotate._x,vec_rotate._y},Point2D{200.0f,200.0f},Color{1.0f,0.0f,0.0f,1.0f});

    /*
     * Rect rect;
     * rect.setPos(100,100); // parent coordinate
     * rect.rotate(90); // local coordinate
     * rect.scale(0.5); //
    */

    draw_rect(QRect(300,300,100,100));

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

void RasterWindow::draw_rect(QRect rect)
{
    float left = rect.left();
    float top = rect.top();
    float right = rect.right();
    float bottom = rect.bottom();

    draw_line_bresenham(Point2D{left,top},Point2D{right,top},Color{1.0f,0.0f,0.0f,1.0f});
    draw_line_bresenham(Point2D{right,top},Point2D{right,bottom},Color{1.0f,0.0f,0.0f,1.0f});
    draw_line_bresenham(Point2D{right,bottom},Point2D{left,bottom},Color{1.0f,0.0f,0.0f,1.0f});
    draw_line_bresenham(Point2D{left,bottom},Point2D{left,top},Color{1.0f,0.0f,0.0f,1.0f});
}
