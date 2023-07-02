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
    changeHeroFrame(ui->playerFrame, ui->labelTopLeft, "Roshan", "Рошан");
}

void MainWindow::on_hero2_clicked()
{
    changeHeroFrame(ui->playerFrame, ui->labelTopLeft, "Shaman", "Регар");
}

void MainWindow::on_hero3_clicked()
{
    changeHeroFrame(ui->playerFrame, ui->labelTopLeft, "Knight", "Гарритос");
}

void MainWindow::on_hero11_clicked()
{
    changeHeroFrame(ui->enemyFrame, ui->labelTopRight, "doomguard", "Дум");
}

void MainWindow::on_hero22_clicked()
{
    changeHeroFrame(ui->enemyFrame, ui->labelTopRight, "Archimonde", "Архимонд");
}

void MainWindow::on_hero33_clicked()
{
    changeHeroFrame(ui->enemyFrame, ui->labelTopRight, "Grunt", "Манкрик");
}

// Метод для изменения Портрета и Имени (fileName = портрет)
void MainWindow::changeHeroFrame(QFrame *heroFrame, QLabel *heroNameLabel, QString fileName, QString heroName) {
    QString baseTemplate = "QFrame {background-image: url(:/images/%1.png); background-position: center; background-repeat: disable}";
    baseTemplate = baseTemplate.arg(fileName);
    heroFrame->setStyleSheet(baseTemplate);
    heroNameLabel->setText(heroName);
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
        invHex *temp = new(invHex);
        temp->setFixedHeight(35);
        temp->setFixedWidth(35);
        temp->setFrameShape(QFrame::Panel);
        temp->setFrameShadow(QFrame::Raised);
        ui->inventoryGrid->addWidget(temp, i_row, i_column);
        i_column++;
        if (i_column == 5) {
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


void MainWindow::on_findSlot_clicked()
{
    int x, y, index;
    x = ui->columnSpinBox->value();
    y = ui->rowSpinBox->value();
    index = ui->indexSpinBox->value();
    if (ui->coordRadio->isChecked()) {
        if (y < ui->inventoryGrid->rowCount()) {
            invHex *temp1 = (invHex*)ui->inventoryGrid->itemAtPosition(y, x)->widget();
            temp1->setStyleSheet("QFrame {background-image: url(:/images/Grunt.png); background-position: center; background-repeat: disable}");
            temp1->i_info.name = "Silver Sword";
            temp1->i_info.quality = qualityStack[countStack];
            temp1->i_info.type = "Sword 2h";
            temp1->i_info.info = "This is really...\nReally cool sword.";
        }
    } else {
        if (index < ui->inventoryGrid->count()) {
            invHex *temp2 = (invHex*)ui->inventoryGrid->itemAt(index)->widget();
            temp2->setStyleSheet("QFrame {background-image: url(:/images/Grunt.png); background-position: center; background-repeat: disable}");
            temp2->i_info.name = "Broken Sword";
            temp2->i_info.quality = qualityStack[countStack];
            temp2->i_info.type = "Sword 1h";
            temp2->i_info.info = "This is really...Really bad sword.";
        }
    }
    countStack++;
    if (countStack == 7)
        countStack = 0;
}

// Наведение мышкой на ячейки ивентаря
bool invHex::event(QEvent *event)
{
    if (event->type() == QEvent::Enter && !showToolTip)
    {
        // Hover enter event
        if (!cursorInsideTooltip) {
            toolTip = new QFrame();
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            QPointF pos = mouseEvent->globalPosition();
            toolTip->setWindowFlags(Qt::ToolTip);
            toolTip->setGeometry(pos.x(), pos.y(), 150, 150);
            toolTip->setFrameShape(QFrame::Box);
            QLabel *toolTipText = new QLabel(toolTip);
            QString textt = "<span style=\"color: %1;\">%2</span>";
            textt = textt.arg(getQualityColor(this->i_info.quality));
            textt = textt.arg(this->i_info.quality);
            toolTipText->setTextFormat(Qt::RichText);
            toolTipText->setWordWrap(true);
            toolTipText->setText(this->i_info.name + "<br><br>" + textt + "<br><br>" + this->i_info.type + "<br><br>" + this->i_info.info);
            toolTipText->setGeometry(0, 0, toolTip->geometry().width(), toolTip->geometry().height());
            toolTipText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            toolTip->show();
            showToolTip = true;
            qDebug() << "Hover Enter";
        }
        // Handle enter event
    }
    else if (event->type() == QEvent::Leave)
    {
        // Hover leave event
        if (!cursorInsideTooltip) {
            delete(toolTip);
            showToolTip = false;
            qDebug() << "Hover Leave";
        }
        // Handle leave event
    }
    else if (event->type() == QEvent::MouseMove)
    {
        // Hover move event
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QPointF pos1 = mouseEvent->globalPosition();
        if (toolTip->geometry().contains(pos1.toPoint())) {
            cursorInsideTooltip = true;
        } else {
            cursorInsideTooltip = false;
            toolTip->setGeometry(pos1.x(), pos1.y(), 150, 150);
            qDebug() << "Hover Move" << pos1;
        }
        // Handle move event
    }
    // ??
    if (!toolTip) {
        showToolTip = false;
        cursorInsideTooltip = false;
    }

    // Call the base class event handler
    return QWidget::event(event);
}
