#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(qreal currentOpacity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    ui->opacityHorizontalSlider->setValue(currentOpacity * 100);
    connect(ui->opacityHorizontalSlider, &QSlider::valueChanged,
            this, &SettingsDialog::opacityChanged);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
