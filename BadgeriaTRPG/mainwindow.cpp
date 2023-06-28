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


void MainWindow::on_hero1_clicked()
{
    ui->playerFrame->setStyleSheet("QFrame {background-image: url(:/images/Roshan.png); background-position: center; background-repeat: disable}");
    ui->labelTopLeft->setText("Рошан");
}


void MainWindow::on_hero2_clicked()
{
    ui->playerFrame->setStyleSheet("QFrame {background-image: url(:/images/Shaman.png); background-position: center; background-repeat: disable}");
    ui->labelTopLeft->setText("Регар");
}


void MainWindow::on_hero3_clicked()
{
    ui->playerFrame->setStyleSheet("QFrame {background-image: url(:/images/Knight.png); background-position: center; background-repeat: disable}");
    ui->labelTopLeft->setText("Гарритос");
}


void MainWindow::on_hero11_clicked()
{
    ui->enemyFrame->setStyleSheet("QFrame {background-image: url(:/images/doomguard.png); background-position: center; background-repeat: disable}");
    ui->labelTopRight->setText("Дум");
}


void MainWindow::on_hero22_clicked()
{
    ui->enemyFrame->setStyleSheet("QFrame {background-image: url(:/images/Archimonde.png); background-position: center; background-repeat: disable}");
    ui->labelTopRight->setText("Архимонд");
}


void MainWindow::on_hero33_clicked()
{
    ui->enemyFrame->setStyleSheet("QFrame {background-image: url(:/images/Grunt.png); background-position: center; background-repeat: disable}");
    ui->labelTopRight->setText("Манкрик");
}


void MainWindow::on_stackSwitcher_2_clicked()
{
    ui->bottomStack->setCurrentIndex(1);
}


void MainWindow::on_stackSwitcher_clicked()
{
    ui->bottomStack->setCurrentIndex(0);
}


void MainWindow::on_questAdd_clicked()
{
    QString temp = "Quest %1:\n\t- Some quest text\n";
    QString temp1 = temp.arg(QString::number(quest_count));
    ui->questList->appendPlainText(temp1);
    quest_count++;
}


void MainWindow::on_addInvSlot_clicked()
{
    QPushButton *temp = new(QPushButton);
    temp->setText("+");
    temp->setStyleSheet("QPushButton {background-image: disable; width: 16px; height: 16px}");
    if (i_column == 3) {
        i_row++;
        i_column = 0;
    }
    ui->inventoryGrid->addWidget(temp, i_row, i_column);
    i_column++;
    if (i_row == 5 && i_column == 3)
        ui->addInvSlot->setDisabled(true);
}


void MainWindow::on_delInvSlot_clicked()
{
    if (i_row > -1 && i_column > -1) {
        ui->inventoryGrid->removeItem(ui->inventoryGrid->itemAtPosition(i_row, i_column - 1));
        i_column--;
        if (i_column == 0 && i_row != 0) {
            i_column = 2;
            i_row--;
        }
    }
}

