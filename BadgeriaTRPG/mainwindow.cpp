#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initHP();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initHP() {
    QString temp = "%1 / %2";
    QString temp1 = temp.arg(e_maxhp);
    QString temp2 = temp1.arg(e_maxhp);
    ui->enemyHPLabel->setText(temp2);
    QString temp3 = "%1 / %2";
    QString temp4 = temp3.arg(p_maxhp);
    QString temp5 = temp4.arg(p_maxhp);
    ui->playerHPLabel->setText(temp5);
}
void MainWindow::on_middleEntry_returnPressed()
{
    if (ui->middleEntry->text() != "")
        ui->middleTextBrowser->append(ui->middleEntry->text());
    if (ui->middleEntry->text() == "clear")
        ui->middleTextBrowser->clear();
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
    for (int i = 0; i < 15; i++) {
        QPushButton *temp = new(QPushButton);
        temp->setText("+");
        temp->setStyleSheet("QPushButton {width: 16px; height: 16px}");
        ui->inventoryGrid->addWidget(temp, i_row, i_column);
        i_column++;
        if (i_column == 3) {
            i_row++;
            i_column = 0;
        }
    }
}

void MainWindow::on_enemyHPSpinBox_valueChanged(int arg1)
{
    e_currhp = arg1;
    double coef = (double)e_maxhp / 100;
    ui->enemyHP->setValue(arg1 / coef);
    QString temp = "%1 / %2";
    QString temp1 = temp.arg(e_currhp);
    QString temp2 = temp1.arg(e_maxhp);
    ui->enemyHPLabel->setText(temp2);
}


void MainWindow::on_playerHPSpinBox_valueChanged(int arg1)
{
    p_currhp = arg1;
    double coef = (double)p_maxhp / 100;
    ui->playerHP->setValue(arg1 / coef);
    QString temp = "%1 / %2";
    QString temp1 = temp.arg(p_currhp);
    QString temp2 = temp1.arg(p_maxhp);
    ui->playerHPLabel->setText(temp2);
}

