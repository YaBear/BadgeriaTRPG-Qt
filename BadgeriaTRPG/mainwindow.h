#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_middleEntry_returnPressed();

    void on_hero1_clicked();

    void on_hero2_clicked();

    void on_hero3_clicked();

    void on_hero11_clicked();

    void on_hero22_clicked();

    void on_hero33_clicked();

    void on_stackSwitcher_2_clicked();

    void on_stackSwitcher_clicked();

    void on_questAdd_clicked();

    void on_addInvSlot_clicked();

    void on_enemyHPSpinBox_valueChanged(int arg1);

    void on_playerHPSpinBox_valueChanged(int arg1);

private:
    int i_row = 0, i_column = 0;
    int quest_count = 0;
    int p_maxhp = 150;
    int e_maxhp = 200;
    int p_currhp = p_maxhp;
    int e_currhp = e_maxhp;
    Ui::MainWindow *ui;
    void initHP();
};
#endif // MAINWINDOW_H
