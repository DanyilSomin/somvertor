#include "movewidget.h"

#include <QMouseEvent>
#include <QWindow>

MoveWidget::MoveWidget(QWidget *parent)
    : QWidget{parent}
{ }

void MoveWidget::mousePressEvent(QMouseEvent *e)
{
    _pressPos = e->pos();
    _moving = true;
}

void MoveWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (_moving) {
        QPoint diff = e->pos() - _pressPos;
        window()->move(window()->pos() + diff);
    }
}

void MoveWidget::mouseReleaseEvent(QMouseEvent *e)
{
    _moving = false;
}


