#include "baserasterwindow.h"
#include <QPainter>
#include <QResizeEvent>
#include <QBackingStore>

BaseRasterWindow::BaseRasterWindow(QWindow *parent)
    : QWindow(parent)
    , mBackingStore(new QBackingStore(this))
{
    setGeometry(200,150,400,400);
}

BaseRasterWindow::~BaseRasterWindow()
{

}

void BaseRasterWindow::render(QPainter *painter)
{
    painter->drawPoint(QPointF(10,10));
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
