#include "righttoolbar.h"

#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QBoxLayout>

const int MinWindowSize = 300;
const int ButtonSize = 9;
const int WidthIconWidth = 7;

const QColor WidthIcon::sColor{ 150, 150, 150, 120 };
const QColor WidthIcon::sColorActive{ 150, 150, 150, 60 };

RightToolBar::RightToolBar(QWidget *parent)
    : QWidget{parent}
{
    setLayout(new QVBoxLayout{ this });

    layout()->setContentsMargins({ 0, 0, 0, 0 });
    layout()->setSpacing(ButtonSize / 3);
    layout()->setAlignment(Qt::AlignCenter);

    auto *widthIcon = new WidthIcon{ this };

    layout()->addWidget(new ClosePushIcon{ this });
    layout()->addWidget(new MinimizePushIcon{ this });
    layout()->addWidget(widthIcon);

    layout()->setAlignment(widthIcon, Qt::AlignHCenter);
}

PushIcon::PushIcon(const QString &pixMap,
                   const QString &activePixMap,
                   QWidget *parent)
     : QWidget{ parent },
    _pixMap{ pixMap },
    _activePixMap{ activePixMap }
{
    setFixedSize({ ButtonSize, ButtonSize });
    setMouseTracking(true);
}

void PushIcon::paintEvent(QPaintEvent *e)
{
    QPainter p{ this };

    p.setRenderHint(QPainter::SmoothPixmapTransform,true);

    if (!_active)
        p.drawPixmap(rect(), _pixMap);
    else
        p.drawPixmap(rect(), _activePixMap);

    return e->accept();
}

void PushIcon::mouseMoveEvent(QMouseEvent *e)
{
    _active = true;
    update();

    return e->accept();
}

void PushIcon::leaveEvent(QEvent *e)
{
    _active = false;
    update();

    return e->accept();
}

ClosePushIcon::ClosePushIcon(QWidget *parent)
    : PushIcon{ QStringLiteral(":/img/close.png"),
                QStringLiteral(":/img/close_active.png"),
                parent }
{ }

void ClosePushIcon::mousePressEvent(QMouseEvent *e)
{
    qApp->quit();

    return e->accept();
}

MinimizePushIcon::MinimizePushIcon(QWidget *parent)
    : PushIcon{ QStringLiteral(":/img/minimize.png"),
                QStringLiteral(":/img/minimize_active.png"),
                parent }
{ }

void MinimizePushIcon::mousePressEvent(QMouseEvent *e)
{
    window()->setWindowState(Qt::WindowMinimized);

    return e->accept();
}

WidthIcon::WidthIcon(QWidget *parent)
{
    setMouseTracking(true);
    setFixedWidth(WidthIconWidth);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
}

void WidthIcon::paintEvent(QPaintEvent *e)
{
    QPainter p{ this };

    const auto fillRect = rect().adjusted(2, 1, -2, -1);

    if (!_active)
        p.fillRect(fillRect, { sColor });
    else
        p.fillRect(fillRect, { sColorActive });

    return e->accept();
}

void WidthIcon::mousePressEvent(QMouseEvent *e)
{
    _moving = true;
    _startGeometry = window()->geometry();
    _startPos = e->globalPosition().toPoint();

    return e->accept();
}

void WidthIcon::mouseDoubleClickEvent(QMouseEvent *e)
{
    QRect windowGeometry = window()->geometry();
    QRect screenGeometry = QApplication::screenAt(
        mapToGlobal(e->pos()))->geometry();

    // double click while maximized
    if (windowGeometry.width() == screenGeometry.width()
     && windowGeometry.left() == screenGeometry.left()) {
        window()->setFixedWidth(_lastDoubleClickGeometry.width());
        window()->setGeometry({ _lastDoubleClickGeometry.left(),
                                windowGeometry.top(),
                                _lastDoubleClickGeometry.width(),
                                _lastDoubleClickGeometry.height()});
    }
    else { // normal double click
        _lastDoubleClickGeometry = windowGeometry;
        window()->setFixedWidth(screenGeometry.width());
        window()->setGeometry({ screenGeometry.left(),
                                windowGeometry.top(),
                                screenGeometry.width(),
                                windowGeometry.height()});
    }

    return e->accept();
}

void WidthIcon::mouseReleaseEvent(QMouseEvent *e)
{
    _moving = false;

    return e->accept();
}

void WidthIcon::mouseMoveEvent(QMouseEvent *e)
{
    _active = true;

    int newWidth = _startGeometry.width()
            - _startPos.x()
            + e->globalPosition().toPoint().x();
    newWidth = std::max(newWidth, MinWindowSize);

    if (_moving) window()->setFixedWidth(newWidth);

    update();

    return e->accept();
}

void WidthIcon::leaveEvent(QEvent *e)
{
    _active = false;
    update();

    return e->accept();
}
