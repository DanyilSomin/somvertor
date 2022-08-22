#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QShortcut>

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
    initShortcuts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStyle(int index)
{
    const auto style = ui->styleComboBox->currentData()
            .value<FormatRules::Style>();

    ui->binSpinBox->setFormatStyle(style);
    ui->decSpinBox->setFormatStyle(style);
    ui->hexSpinBox->setFormatStyle(style);
}

void MainWindow::increment()
{
    const auto currentNum = ui->binSpinBox->getBigInt();
    const auto incremented = BigInt::incremented(currentNum);

    const auto applyIncrement = [&](auto *sb) {
        sb->setBigInt(incremented);
        sb->update();
    };

    applyIncrement(ui->binSpinBox);
    applyIncrement(ui->decSpinBox);
    applyIncrement(ui->hexSpinBox);
}

void MainWindow::decrement()
{
    const auto currentNum = ui->binSpinBox->getBigInt();
    const auto decremented = BigInt::decremented(currentNum);

    const auto applyDecrement = [&](auto *sb) {
        sb->setBigInt(decremented);
        sb->update();
    };

    applyDecrement(ui->binSpinBox);
    applyDecrement(ui->decSpinBox);
    applyDecrement(ui->hexSpinBox);
}

void MainWindow::switchStyle()
{
    auto *combo = ui->styleComboBox;
    const auto count = combo->count();
    const auto currentIndex = combo->currentIndex();
    const auto nextIndex = (combo->currentIndex() + 1) % combo->count();

    ui->styleComboBox->setCurrentIndex(nextIndex);
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

        connect(sb, &BigIntSpinBox::incrementPressed,
                this, &MainWindow::increment);
        connect(sb, &BigIntSpinBox::decrementPressed,
                this, &MainWindow::decrement);
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

    connect(ui->styleComboBox, &QComboBox::currentIndexChanged,
            this, &MainWindow::updateStyle);
}

void MainWindow::initShortcuts()
{
    connect(new QShortcut(QKeySequence("Ctrl+s"), this), &QShortcut::activated,
            this, &MainWindow::switchStyle);
    connect(new QShortcut(QKeySequence("Ctrl+і"), this), &QShortcut::activated,
            this, &MainWindow::switchStyle);
}

