#pragma once

#include <QMainWindow>
#include <QSettings>

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

private slots:
    void updateStyle(int index);
    void increment();
    void decrement();
    void switchStyle();

private:
    void initSpinBoxes();
    void initStyleComboBox();
    void initShortcuts();
    void initSettings();

    QSettings _settings{ QSettings::Format::IniFormat, QSettings::UserScope, "settings.ini" };

    Ui::MainWindow *ui;

    static const QString propOpacity;
};
