#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::FramelessWindowHint
                 | Qt::WindowSystemMenuHint
                 | Qt::WindowStaysOnTopHint);

    ui->setupUi(this);

    initSpinBoxes();
    initStyleComboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSpinBoxes()
{
    ui->binSpinBox->init(FormatRules::Style::Plain, BigInt::Digits::Bin);
    ui->decSpinBox->init(FormatRules::Style::Plain, BigInt::Digits::Dec);
    ui->hexSpinBox->init(FormatRules::Style::Plain, BigInt::Digits::Hex);

    auto connectSpinBox = [&](BigIntSpinBox *sb) {
        connect(sb, &BigIntSpinBox::valueEdited, this,
        [&, sb](const auto &bigInt) {
            if (sb != ui->binSpinBox)
                ui->binSpinBox->setBigInt(bigInt);
            if (sb != ui->decSpinBox)
                ui->decSpinBox->setBigInt(bigInt);
            if (sb != ui->hexSpinBox)
                ui->hexSpinBox->setBigInt(bigInt);
        });
    };

    connectSpinBox(ui->binSpinBox);
    connectSpinBox(ui->decSpinBox);
    connectSpinBox(ui->hexSpinBox);
}

void MainWindow::initStyleComboBox()
{
    for (const auto style : FormatRules::styles) {
        ui->styleComboBox->addItem(
                    FormatRules::styleName(style),
                    QVariant::fromValue(style));
    }

    connect(ui->styleComboBox, &QComboBox::currentIndexChanged, this,
            [&](int index) {
                const auto style = ui->styleComboBox->currentData()
                        .value<FormatRules::Style>();

                ui->binSpinBox->setFormatStyle(style);
                ui->decSpinBox->setFormatStyle(style);
                ui->hexSpinBox->setFormatStyle(style);
            });
}

