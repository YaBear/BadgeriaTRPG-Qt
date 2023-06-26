#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_middleEntry_returnPressed()
{
    if (ui->middleEntry->text() != "")
        ui->middleTextBrowser->append(ui->middleEntry->text());
    ui->middleEntry->clear();
}

