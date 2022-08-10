#include "movewidget.h"

#include <QMouseEvent>

MoveWidget::MoveWidget(QWidget *parent)
    : QWidget{parent}
{

}

void MoveWidget::mousePressEvent(QMouseEvent *e)
{
    _startEventPos = e->position().toPoint();
    _startWindowPos = parentWidget()->pos();
    _moving = true;
}

void MoveWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (!_moving) return;

    QPoint offset{ e->position().toPoint() - _startEventPos };
    parentWidget()->move(_startWindowPos + offset);
}

void MoveWidget::mouseReleaseEvent(QMouseEvent *e)
{
    _moving = false;
}


