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
    // QTimer *timer = new QTimer(this);
    // connect(timer,SIGNAL(timeout()),this,SLOT(renderNow()));
    // timer->start(16);
}

RasterWindow::~RasterWindow()
{

}

void RasterWindow::render(QPainter *painter)
{
    int x0 = 400;
    int y0 = 400;
    int x1 = 600;
    int y1 = 10;
    // static bool x_grow = true;

    painter->setPen(QColor(0,100,0));

    // auto start1 = std::chrono::steady_clock::now();

    draw_line_dda(painter,QPoint(x0,y0),QPoint(x1,y1));

    // auto end1 = std::chrono::steady_clock::now();
    // qDebug() << "dda duration:" << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << "us";

//    if(x_grow)
//        x1 += 1;
//    else x1 -= 1;
//    if(x1 > 800) {
//        x_grow = false;
//    } else if(x1 < 0) {
//        x_grow = true;
//    }

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
    float k = 0;
    int dx = end.x() - start.x();
    int dy = end.y() - start.y();

    if(dx)
        k = static_cast<float>(dy) / static_cast<float>(dx);

    float x = start.x();
    float y = static_cast<float>(start.y());
    if(std::abs(dy) <= std::abs(dx)) {
        for(int i = 0; i < abs(dx); ++i) {
            painter->drawPoint(static_cast<int>(x),static_cast<int>(y+0.5f));
            if(dx>0)
                x += 1;
            else if(dx<0)
                x -= 1;
            if(k < 0) {
                if(dy>0)
                    y += abs(k);
                else y += k;
            } else {
                y += k;
            }
        }
    } else {
        for(int i = 0; i < abs(dy); ++i) {
            painter->drawPoint(static_cast<int>(x+0.5f),static_cast<int>(y));
            if(dy>0)
                y += 1;
            else if(dy<0)
                y -= 1;

            if(k > 0) {
                if(dx<0)
                    x += abs(k);
                else x += k;
            } else {
                x += k;
            }
        }
    }
}
