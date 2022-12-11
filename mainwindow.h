#pragma once

#include <QMainWindow>
#include <QSettings>

Q_DECLARE_METATYPE(std::vector<QString>);

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onOpacityChanged(int opacity);
    void onStyleChanged(int style);
    void onBigIntChanged(const std::vector<bool> &bigInt, QObject *caller);

private slots:
    void updateStyle();
    void increment();
    void decrement();
    void switchStyle();

private:
    void initSpinBoxes();
    void initStyleComboBox();
    void initShortcuts();
    void initOpacity();

    QSettings _settings{ QSettings::Format::IniFormat, QSettings::UserScope, "settings.ini" };

    Ui::MainWindow *ui;

    static const QString propOpacity;
    static const QString propStyle;
    static const QString propBigInt;
};
