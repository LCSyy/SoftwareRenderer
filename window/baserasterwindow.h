#ifndef BASERASTERWINDOW_H
#define BASERASTERWINDOW_H

#include <QWindow>

class QBackingStore;

class BaseRasterWindow: public QWindow
{
    Q_OBJECT
public:
    explicit BaseRasterWindow(QWindow *parent = nullptr);
    ~BaseRasterWindow() override;

    virtual void render(QPainter *painter);

public slots:
    void renderLater();
    void renderNow();

protected:
    virtual void _init();
    virtual void _update(float delta);
    virtual void _final();

    bool event(QEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void exposeEvent(QExposeEvent *e) override;

protected:
    QPainter *_painter{nullptr};
    bool mInitailized{false};
    bool mFinalized{false};

private:
    QBackingStore *mBackingStore{nullptr};
};

#endif // BASERASTERWINDOW_H
