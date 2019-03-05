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

    void draw_point(int x, int y, const Color &color) override;

protected:
    void _init() override;
    void _update(float delta) override;
    void _final() override;

private:
    SceneNode *scene{nullptr};
    std::vector<Animation*> anims{nullptr};
};

#endif // RASTERWINDOW_H
