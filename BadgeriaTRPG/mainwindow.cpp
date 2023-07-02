#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  initHP();
}

MainWindow::~MainWindow() { delete ui; }

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
void MainWindow::on_middleEntry_returnPressed() {
  if (ui->middleEntry->text() != "")
    ui->middleTextBrowser->append(ui->middleEntry->text());
  if (ui->middleEntry->text() == "clear") ui->middleTextBrowser->clear();
  ui->middleEntry->clear();
}

void MainWindow::on_hero1_clicked() {
  changeHeroFrame(ui->playerFrame, ui->labelTopLeft, "Roshan", "Рохан");
}

void MainWindow::on_hero2_clicked() {
  changeHeroFrame(ui->playerFrame, ui->labelTopLeft, "Shaman", "Регар");
}

void MainWindow::on_hero3_clicked() {
  changeHeroFrame(ui->playerFrame, ui->labelTopLeft, "Knight", "Гарритос");
}

void MainWindow::on_hero11_clicked() {
  changeHeroFrame(ui->enemyFrame, ui->labelTopRight, "doomguard", "Дум");
}

void MainWindow::on_hero22_clicked() {
  changeHeroFrame(ui->enemyFrame, ui->labelTopRight, "Archimonde", "Архимонд");
}

void MainWindow::on_hero33_clicked() {
  changeHeroFrame(ui->enemyFrame, ui->labelTopRight, "Grunt", "Манкрик");
}

// Метод для изменения Портрета и Имени (fileName = портрет)
void MainWindow::changeHeroFrame(QFrame *heroFrame, QLabel *heroNameLabel,
                                 QString fileName, QString heroName) {
  QString baseTemplate =
      "QFrame {background-image: url(:/images/%1.png); background-position: "
      "center; background-repeat: disable}";
  baseTemplate = baseTemplate.arg(fileName);
  heroFrame->setStyleSheet(baseTemplate);
  heroNameLabel->setText(heroName);
}

void MainWindow::on_stackSwitcher_2_clicked() {
  ui->bottomStack->setCurrentIndex(1);
}

void MainWindow::on_stackSwitcher_clicked() {
  ui->bottomStack->setCurrentIndex(0);
}

void MainWindow::on_questAdd_clicked() {
  QString temp = "Quest %1:\n\t- Some quest text\n";
  QString temp1 = temp.arg(QString::number(quest_count));
  ui->questList->appendPlainText(temp1);
  quest_count++;
}

void MainWindow::on_addInvSlot_clicked() {
  for (int i = 0; i < 15; i++) {
    invHex *temp = new (invHex);
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

void MainWindow::on_enemyHPSpinBox_valueChanged(int arg1) {
  e_currhp = arg1;
  double coef = (double)e_maxhp / 100;
  ui->enemyHP->setValue(arg1 / coef);
  QString temp = "%1 / %2";
  QString temp1 = temp.arg(e_currhp);
  QString temp2 = temp1.arg(e_maxhp);
  ui->enemyHPLabel->setText(temp2);
}

void MainWindow::on_playerHPSpinBox_valueChanged(int arg1) {
  p_currhp = arg1;
  double coef = (double)p_maxhp / 100;
  ui->playerHP->setValue(arg1 / coef);
  QString temp = "%1 / %2";
  QString temp1 = temp.arg(p_currhp);
  QString temp2 = temp1.arg(p_maxhp);
  ui->playerHPLabel->setText(temp2);
}

void MainWindow::on_addSlot_clicked() {
  int x, y, index;
  x = ui->columnSpinBox->value();
  y = ui->rowSpinBox->value();
  index = ui->indexSpinBox->value();
  if (ui->coordRadio->isChecked()) {
    if (y < ui->inventoryGrid->rowCount()) {
      invHex *temp1 =
          (invHex *)ui->inventoryGrid->itemAtPosition(y, x)->widget();
      temp1->setStyleSheet(
          "QFrame {background-image: url(:/images/10.jpg); "
          "background-position: center; background-repeat: disable}");
      temp1->i_info.name = "Silver Sword";
      temp1->i_info.quality = qualityStack[countStack];
      temp1->i_info.type = "Sword 2h";
      temp1->i_info.info = "This is really...\nReally cool sword.";
      temp1->i_info.exist = true;
    }
  } else {
    if (index < ui->inventoryGrid->count()) {
      invHex *temp2 = (invHex *)ui->inventoryGrid->itemAt(index)->widget();
      temp2->setStyleSheet(
          "QFrame {background-image: url(:/images/8.jpg); background-position: "
          "center; background-repeat: disable}");
      temp2->i_info.name = "Broken Sword";
      temp2->i_info.quality = qualityStack[countStack];
      temp2->i_info.type = "Sword 1h";
      temp2->i_info.info = "This is really...Really bad sword.";
      temp2->i_info.exist = true;
      temp2->i_info.equipable = true;
    }
  }
  if (countStack++ == 6) countStack = 0;
}

// Наведение мышкой на ячейки ивентаря
bool invHex::event(QEvent *event) {
  if (event->type() == QEvent::Enter && !showToolTip && i_info.exist) {
    toolTip = new QFrame();
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    QPointF pos = mouseEvent->globalPosition();
    toolTip->setWindowFlags(Qt::ToolTip);
    toolTip->setGeometry(pos.x() + 20, pos.y() + 20, 150, 150);
    toolTip->setFrameShape(QFrame::Box);
    QLabel *toolTipText = new QLabel(toolTip);
    QString textt = "<span style=\"color: %1;\">%2</span>";
    textt = textt.arg(getQualityColor(i_info.quality));
    textt = textt.arg(i_info.quality);
    toolTipText->setTextFormat(Qt::RichText);
    toolTipText->setWordWrap(true);
    toolTipText->setText(i_info.name + "<br><br>" + textt + "<br><br>" +
                         i_info.type + "<br><br>" + i_info.info);
    toolTipText->setGeometry(0, 0, toolTip->geometry().width(),
                             toolTip->geometry().height());
    toolTipText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    toolTip->show();
    showToolTip = true;
    //            qDebug() << "Hover Enter";
  } else if (event->type() == QEvent::Leave && i_info.exist) {
    delete (toolTip);
    showToolTip = false;
    //            qDebug() << "Hover Leave";
  } else if (event->type() == QEvent::MouseMove && i_info.exist) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    QPointF pos1 = mouseEvent->globalPosition();
    toolTip->setGeometry(pos1.x() + 20, pos1.y() + 20, 150, 150);
    //            qDebug() << "Hover Move" << pos1;
    // Handle move event
  } else if (event->type() == QEvent::MouseButtonPress) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if (mouseEvent->buttons() == Qt::LeftButton && i_info.exist) {
      QPointF pos = mouseEvent->globalPosition();
      i_menu.inv_menu = new QFrame();
      i_menu.inv_menu->setWindowFlags(Qt::SplashScreen);
      i_menu.inv_menu->setGeometry(pos.x() + 20, pos.y() + 20, 150, 100);
      i_menu.inv_menu->setFrameShape(QFrame::Box);
      i_menu.equip_b = new QPushButton(i_menu.inv_menu);
      connect(i_menu.equip_b, SIGNAL(clicked()), this,
              SLOT(on_equip_b_clicked()));
      i_menu.equip_b->setText("Надеть");
      i_menu.equip_b->setGeometry(0, 0, 150, 30);
      if (!i_info.equipable) i_menu.equip_b->setDisabled(true);
      i_menu.equip_b->show();
      i_menu.drop_b = new QPushButton(i_menu.inv_menu);
      connect(i_menu.drop_b, SIGNAL(clicked()), this,
              SLOT(on_drop_b_clicked()));
      i_menu.drop_b->setText("Выбросить");
      i_menu.drop_b->setGeometry(0, 35, 150, 30);
      i_menu.drop_b->show();
      i_menu.cancel_b = new QPushButton(i_menu.inv_menu);
      connect(i_menu.cancel_b, SIGNAL(clicked()), this,
              SLOT(on_cancel_b_clicked()));
      i_menu.cancel_b->setText("Закрыть");
      i_menu.cancel_b->setGeometry(0, 70, 150, 30);
      i_menu.cancel_b->show();
      i_menu.inv_menu->show();
    }
  }
  return QWidget::event(event);
}
