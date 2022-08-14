#pragma once

#include <QWidget>

const int MinWindowSize = 300;
const int ButtonSize = 9;
const int WidthIconWidth = 3;

class RightToolBar : public QWidget
{
public:
    explicit RightToolBar(QWidget *parent = nullptr);
};

class PushIcon : public QWidget
{
public:
    virtual void paintEvent(QPaintEvent *e) override;
    virtual void mousePressEvent(QMouseEvent *e) override = 0;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void leaveEvent(QEvent *e) override;

    virtual ~PushIcon() = default;

protected:
    explicit PushIcon(const QString &pixMap,
                      const QString &activePixMap,
                      QWidget *parent = nullptr);

private:
    QPixmap _pixMap;
    QPixmap _activePixMap;
    bool _active = false;
};

class ClosePushIcon : public PushIcon {
public:
    explicit ClosePushIcon(QWidget *parent);
    virtual void mousePressEvent(QMouseEvent *e) override;
};

class MinimizePushIcon : public PushIcon {
public:
    explicit MinimizePushIcon(QWidget *parent);
    virtual void mousePressEvent(QMouseEvent *e) override;
};

class WidthIcon : public QWidget
{
public:
    explicit WidthIcon(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *e) override;
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void leaveEvent(QEvent *e) override;

private:
    QRect _startGeometry{ };
    QPoint _startPos{ };

    bool _moving{ false };
    bool _active{ false };
};
