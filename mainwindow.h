#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateStyle(int index);
    void increment();
    void decrement();

private:
    void initSpinBoxes();
    void initStyleComboBox();
    void initHokeys();

    Ui::MainWindow *ui;
};
