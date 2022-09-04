#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(qreal currentOpacity, QWidget *parent = nullptr);
    ~SettingsDialog();

signals:
    void opacityChanged(int opacity);

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
