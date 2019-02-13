#ifndef RASTERWINDOW_H
#define RASTERWINDOW_H

#include "baserasterwindow.h"

class RasterWindow: public BaseRasterWindow
{
    Q_OBJECT
public:
    explicit RasterWindow(QWindow *parent = nullptr);
    ~RasterWindow() override;

    void render(QPainter *painter) override;

    void draw_line_formula(QPainter *painter, QPoint start, QPoint end);
    void draw_line_dda(QPainter *painter, QPoint start, QPoint end);
    void draw_line_midpoint(QPainter *painter, QPoint start, QPoint end);
    void draw_line_bresenham(QPainter *painter, QPoint start, QPoint end);

};

#endif // RASTERWINDOW_H
