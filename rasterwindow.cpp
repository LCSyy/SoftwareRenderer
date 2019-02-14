#include "rasterwindow.h"
#include <QImage>
#include <QPainter>
#include <QTimer>
#include <cmath>
#include <chrono>

#include <QDebug>

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
    int x0 = 400;
    int y0 = 400;
    static int x1 = 0;
    static int y1 = 0;
    static bool x_grow = true;

    painter->setPen(QColor(0,100,0));

    // auto start1 = std::chrono::steady_clock::now();

    // draw_line_dda(painter,QPoint(x0,y0),QPoint(x1,y1));
    draw_line_bresenham(painter,QPoint(x0,y0),QPoint(x1,y1));
    // auto end1 = std::chrono::steady_clock::now();
    // qDebug() << "dda duration:" << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << "us";

    if(x_grow)
        y1 += 1;
    else y1 -= 1;
    if(y1 > 800) {
        x_grow = false;
    } else if(y1 < 0) {
        x_grow = true;
    }
}

void RasterWindow::draw_line_formula(QPainter *painter, QPoint start, QPoint end)
{
    int x0 = start.x();
    int y0 = start.y();
    int x1 = end.x();
    int y1 = end.y();

    float k = static_cast<float>(y1-y0) / static_cast<float>(x1-x0);
    float b = y0 - k * static_cast<float>(x0);

    int dy = y1 - y0;
    for(int i = 0; i <= std::abs(dy); ++i) {
        int y = y0+(dy-i);
        int x = static_cast<int>((static_cast<float>(y) - b)/k);
        painter->drawPoint(x,y);
    }
}

void RasterWindow::draw_line_dda(QPainter *painter, QPoint start, QPoint end)
{
    int dx = end.x() - start.x();
    int dy = end.y() - start.y();

    int stride = 0;
    if(std::abs(dy) <= std::abs(dx))
        stride = std::abs(dx);
    else
        stride = std::abs(dy);

    float step_x = 0.0f;
    float step_y = 1.0f;

    if(stride) {
        step_x = dx / static_cast<float>(stride);
        step_y = dy / static_cast<float>(stride);
    }

    float x = static_cast<float>(start.x());
    float y = static_cast<float>(start.y());

    for(int i = 0; i < stride; ++i) {
        painter->drawPoint(static_cast<int>(x+0.5f),static_cast<int>(y+0.5f));
        x += step_x;
        y += step_y;
    }
}

void RasterWindow::draw_line_midpoint(QPainter *painter, QPoint start, QPoint end)
{

}

void RasterWindow::draw_line_bresenham(QPainter *painter, QPoint start, QPoint end)
{
    int dx = end.x() - start.x();
    int dy = end.y() - start.y();

    auto plotLow = [&painter,&dx,&dy](int x0, int y0, int x1){
        int yi = 1;
        if(dy<0) {
            yi = -1;
            dy = -dy;
        }
        int D = 2 * dy - dx;
        int y = y0;

        for(int x = x0; x < x1; ++x) {
            painter->drawPoint(x,y);
            if(D > 0) {
                y += yi;
                D = D - 2 * dx;
            }
            D = D + 2 * dy;
        }
    };

    auto plotHigh = [&painter,&dx,&dy](int x0, int y0, int y1){
        int xi = 1;
        if(dx < 0) {
            xi = -1;
            dx = -dx;
        }
        int D = 2 * dx - dy;
        int x = x0;
        for(int y = y0; y < y1; ++y) {
            painter->drawPoint(x,y);
            if(D > 0) {
                x += xi;
                D = D - 2 * dy;
            }
            D = D + 2 * dx;
        }
    };

    if(std::abs(dy) <= std::abs(dx)) {
        if(dx<=0) {
            plotLow(end.x(),end.y(),start.x());
        } else {
            plotLow(start.x(),start.y(),end.x());
        }
    } else {
        if(dy<=0) {
            plotHigh(end.x(),end.y(),start.y());
        } else {
            plotHigh(start.x(),start.y(),end.y());
        }
    }
}
