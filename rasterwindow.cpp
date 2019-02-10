#include "rasterwindow.h"
#include <QPainter>
#include <QResizeEvent>
#include <QBackingStore>

RasterWindow::RasterWindow(QWindow *parent)
    : QWindow(parent)
    , mBackingStore(new QBackingStore(this))
{
    setGeometry(200,150,400,400);
}

RasterWindow::~RasterWindow()
{

}

void RasterWindow::render(QPainter *painter)
{
    painter->drawPoint(10,10);
}

void RasterWindow::renderLater()
{
    requestUpdate();
}

void RasterWindow::renderNow()
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

bool RasterWindow::event(QEvent *e)
{
    if (e->type() == QEvent::UpdateRequest) {
        renderNow();
        return true;
    }
    return QWindow::event(e);
}

void RasterWindow::resizeEvent(QResizeEvent *e)
{
    mBackingStore->resize(e->size());
}

void RasterWindow::exposeEvent(QExposeEvent *e)
{
    Q_UNUSED(e)

    if (isExposed())
        renderNow();
}
