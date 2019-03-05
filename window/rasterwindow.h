#ifndef RASTERWINDOW_H
#define RASTERWINDOW_H

#include "baserasterwindow.h"
#include "rasterizer/rasterizeengine.h"

class SceneNode;
class Animation;
class RasterWindow: public BaseRasterWindow, public RasterizeEngine
{
    Q_OBJECT
public:
    explicit RasterWindow(QWindow *parent = nullptr);
    ~RasterWindow() override;

    void render(QPainter *painter) override;

    void draw_point(int x, int y, const Color &color) override;

    void draw_rect(QRect rect);

protected:
    void _update(float delta);

private:
    QPainter *_painter{nullptr};

    SceneNode *scene{nullptr};
    std::vector<Animation*> anims{nullptr};
};

#endif // RASTERWINDOW_H
