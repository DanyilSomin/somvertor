#ifndef MOVEWIDGET_H
#define MOVEWIDGET_H

#include <QWidget>
#include <QPoint>

class MoveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MoveWidget(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

    QWindow *window() const;
    void setWindow(QWindow *newWindow);

private:
    QPoint _startEventPos{ 0, 0 };
    QPoint _startWindowPos{ 0, 0 };
    bool _moving{ true };
};

#endif // MOVEWIDGET_H
