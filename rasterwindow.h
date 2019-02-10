#ifndef RASTERWINDOW_H
#define RASTERWINDOW_H

#include <QWindow>

class QBackingStore;

class RasterWindow: public QWindow
{
    Q_OBJECT
public:
    explicit RasterWindow(QWindow *parent = nullptr);
    ~RasterWindow() override;

    virtual void render(QPainter *painter);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *e) override;

    void resizeEvent(QResizeEvent *e) override;
    void exposeEvent(QExposeEvent *e) override;

private:
    QBackingStore *mBackingStore{nullptr};
};

#endif // RASTERWINDOW_H
