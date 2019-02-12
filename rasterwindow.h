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
};

#endif // RASTERWINDOW_H
