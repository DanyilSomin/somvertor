#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QShortcut>

const QString MainWindow::propOpacity = QStringLiteral("app/opacity");
const QString MainWindow::propStyle = QStringLiteral("app/style");
const QString MainWindow::propBigInt = QStringLiteral("app/bigint");

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);

    ui->setupUi(this);

    initSpinBoxes();
    initStyleComboBox();
    initShortcuts();
    initOpacity();
}

MainWindow::~MainWindow()
{
    delete ui;
    _settings.sync();
}

void MainWindow::updateStyle()
{
    const auto style = ui->styleComboBox->currentData().value<FormatRules::Style>();

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
    const auto nextIndex = (currentIndex + 1) % count;

    ui->styleComboBox->setCurrentIndex(nextIndex);
}

void MainWindow::onOpacityChanged(int opacity)
{
    const qreal newOpacity = opacity / 100.0;
    _settings.setValue(propOpacity, opacity);
    setWindowOpacity(newOpacity);
}

void MainWindow::onStyleChanged(int style)
{
    _settings.setValue(propStyle, style);
    ui->styleComboBox->setCurrentIndex(style);
    updateStyle();
}

void MainWindow::onBigIntChanged(const std::vector<bool> &bigInt, QObject *caller)
{
    if (caller != ui->binSpinBox)
        ui->binSpinBox->setBigInt(bigInt);
    if (caller != ui->decSpinBox)
        ui->decSpinBox->setBigInt(bigInt);
    if (caller != ui->hexSpinBox)
        ui->hexSpinBox->setBigInt(bigInt);
}

void MainWindow::initSpinBoxes()
{
    ui->binSpinBox->init(FormatRules::Style::Plain, BigInt::Digits::Bin);
    ui->decSpinBox->init(FormatRules::Style::Plain, BigInt::Digits::Dec);
    ui->hexSpinBox->init(FormatRules::Style::Plain, BigInt::Digits::Hex);

    auto connectSpinBox = [&](BigIntSpinBox *sb) {
        connect(sb, &BigIntSpinBox::valueEdited, this, &MainWindow::onBigIntChanged);
        connect(sb, &BigIntSpinBox::incrementPressed, this, &MainWindow::increment);
        connect(sb, &BigIntSpinBox::decrementPressed, this, &MainWindow::decrement);
    };

    connectSpinBox(ui->binSpinBox);
    connectSpinBox(ui->decSpinBox);
    connectSpinBox(ui->hexSpinBox);
}

void MainWindow::initStyleComboBox()
{
    for (const auto style : FormatRules::styles)
    {
        ui->styleComboBox->addItem(FormatRules::styleName(style), QVariant::fromValue(style));
    }

    ui->styleComboBox->setCurrentIndex(_settings.value(propStyle, 0).toInt());
    updateStyle();
    connect(ui->styleComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::onStyleChanged);
}

void MainWindow::initShortcuts()
{
    connect(new QShortcut(QKeySequence("Ctrl+s"), this), &QShortcut::activated, this,
            &MainWindow::switchStyle);
    connect(new QShortcut(QKeySequence("Ctrl+і"), this), &QShortcut::activated, this,
            &MainWindow::switchStyle);
}

void MainWindow::initOpacity()
{
    const auto opacity = _settings.value(propOpacity, 100).toInt();
    setWindowOpacity(std::max(opacity / 100.0, 0.1));
    ui->opacityHorizontalSlider->setValue(opacity);
    connect(ui->opacityHorizontalSlider, &QSlider::valueChanged, this,
            &MainWindow::onOpacityChanged);
}
