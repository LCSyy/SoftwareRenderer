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
    bool event(QEvent *e) override;

    void resizeEvent(QResizeEvent *e) override;
    void exposeEvent(QExposeEvent *e) override;

private:
    QBackingStore *mBackingStore{nullptr};
};

#endif // BASERASTERWINDOW_H
