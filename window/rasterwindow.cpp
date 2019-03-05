#include "rasterwindow.h"
#include <QImage>
#include <QPen>
#include <QPainter>
#include <QTimer>
#include <cmath>
#include <chrono>

#include <QDebug>

#include "math/vector.h"
#include "scene/scenenode.h"
#include "scene/animation.h"

RasterWindow::RasterWindow(QWindow *parent)
    : BaseRasterWindow(parent)
{
     QTimer *timer = new QTimer(this);
     connect(timer,SIGNAL(timeout()),this,SLOT(renderNow()));
     timer->start(16);
}

RasterWindow::~RasterWindow()
{
    for(Animation *anim: anims) {
        if(anim) delete anim;
    }
    if(scene)
        delete scene;

}

void RasterWindow::render(QPainter *painter)
{
    _painter = painter;

    // static auto last_time = std::chrono::system_clock::now();
    // auto frame_now = std::chrono::system_clock::now();
    // std::chrono::duration<float,std::ratio<1,1>> diff = frame_now-last_time;

    _update(0.0f);

    // last_time = frame_now;
    _painter = nullptr;
}

void RasterWindow::_update(float delta)
{
    Q_UNUSED(delta)

    if(!scene) {
        scene = new SceneNode({Point2D{0,0},Point2D{100,0},Point2D{100,100},Point2D{0,100}},nullptr);

        Animation *x_anim = new Animation;
        anims.push_back(x_anim);
        x_anim->attachPropertyAnimation(&scene->transform().mTranslation._x,0.0f,600.0f,1.0f);
    }

    for(size_t i = 0, i2 = 1; i < scene->data().size(); ++i, i2 = i + 1) {
        if(i == scene->data().size() - 1) {
            i2 = 0;
        }
        draw_line_bresenham(scene->transformedData(i),scene->transformedData(i2),Color{1.0f,0.0f,0.0f,1.0f});
    }

    for(Animation *anim: anims) {
        if(anim)
            anim->play();
    }
}

void RasterWindow::draw_point(int x, int y, const Color &color)
{
    if(_painter) {
        _painter->setPen(QColor::fromRgbF(static_cast<double>(color.r), static_cast<double>(color.g),
                                          static_cast<double>(color.b), static_cast<double>(color.a)));
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
