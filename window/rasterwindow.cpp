#include "rasterwindow.h"
#include <cmath>
#include <chrono>
#include <QImage>
#include <QPen>
#include <QPainter>
#include <QTimer>

#include "math/vector.h"
#include "scene/scenenode.h"
#include "scene/animation.h"

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

void RasterWindow::draw_point(int x, int y, const Color &color)
{
    if(_painter) {
        _painter->setPen(QColor::fromRgbF(static_cast<double>(color.r), static_cast<double>(color.g),
                                          static_cast<double>(color.b), static_cast<double>(color.a)));
        _painter->drawPoint(x,y);
    }
}

void RasterWindow::_init()
{
    if(!scene) {
        scene = new SceneNode({Point2D{0,0},Point2D{100,0},Point2D{100,100},Point2D{0,100}},nullptr);

        Animation *x_anim = new Animation;
        anims.push_back(x_anim);
        x_anim->attachProperty(&scene->transform().mTranslation._x,0.0f,600.0f,1.0f);
    }
}

void RasterWindow::_update(float delta)
{
    Q_UNUSED(delta)

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

void RasterWindow::_final()
{
    for(Animation *anim: anims) {
        if(anim) delete anim;
    }
    if(scene)
        delete scene;
}

// https://blog.csdn.net/smilejiasmile/article/details/79606234
