#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->binSpinBox->init(FormatRules::Style::Plain, BigInt::Digits::Bin);
    ui->decSpinBox->init(FormatRules::Style::Plain, BigInt::Digits::Dec);
    ui->hexSpinBox->init(FormatRules::Style::Plain, BigInt::Digits::Hex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

