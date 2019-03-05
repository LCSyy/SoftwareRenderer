#include "baserasterwindow.h"
#include <QGuiApplication>
#include <QPainter>
#include <QResizeEvent>
#include <QBackingStore>

BaseRasterWindow::BaseRasterWindow(QWindow *parent)
    : QWindow(parent)
    , mBackingStore(new QBackingStore(this))
{
    setGeometry(100,100,800,800);
    connect(qGuiApp,&QGuiApplication::aboutToQuit,[this](){
        _final();
    });
}

BaseRasterWindow::~BaseRasterWindow()
{
}

void BaseRasterWindow::render(QPainter *painter)
{
    _painter = painter;

     if(!mInitailized) {
         mInitailized = true;
         _init();
     }

     // static auto last_time = std::chrono::system_clock::now();
     // auto frame_now = std::chrono::system_clock::now();
     // std::chrono::duration<float,std::ratio<1,1>> diff = frame_now-last_time;
     _update(0.0f);
     // last_time = frame_now;

     _painter = nullptr;
}

void BaseRasterWindow::renderLater()
{
    requestUpdate();
}

void BaseRasterWindow::renderNow()
{
    if (!isExposed())
        return;

    QRect rect(0, 0, width(), height());
    mBackingStore->beginPaint(rect);
    QPaintDevice *device = mBackingStore->paintDevice();
    QPainter painter(device);
    painter.fillRect(0, 0, width(), height(), QGradient::NightFade);

    render(&painter);

    painter.end();
    mBackingStore->endPaint();
    mBackingStore->flush(rect);
}

void BaseRasterWindow::_init()
{

}

void BaseRasterWindow::_update(float delta)
{

}

void BaseRasterWindow::_final()
{

}

bool BaseRasterWindow::event(QEvent *e)
{
    if (e->type() == QEvent::UpdateRequest) {
        renderNow();
        return true;
    }
    return QWindow::event(e);
}

void BaseRasterWindow::resizeEvent(QResizeEvent *e)
{
    mBackingStore->resize(e->size());
}

void BaseRasterWindow::exposeEvent(QExposeEvent *e)
{
    Q_UNUSED(e)

    if (isExposed())
        renderNow();
}
