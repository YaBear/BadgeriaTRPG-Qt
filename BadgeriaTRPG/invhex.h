#ifndef INVHEX_H
#define INVHEX_H

#include <QFrame>
#include <QMouseEvent>

#include "mainwindow.h"

class invHex : public QFrame {
  Q_OBJECT

 public:
  typedef struct Info_s {
    QString name;
    QString quality;
    QString type;
    QString info;
    bool exist;
    bool equipable;
    bool equiped;
    int x;
    int y;
  } Item_Info;
  typedef struct Menu_s {
    QFrame *inv_menu = nullptr;
    QPushButton *equip_b = nullptr;
    QPushButton *drop_b = nullptr;
    QPushButton *cancel_b = nullptr;
  } Menu_Inv;

  Item_Info i_info = {"", "", "", "", false, false, false, 0, 0};
  Menu_Inv i_menu;

  explicit invHex(QWidget *parent = nullptr);
  bool event(QEvent *event) override;

 private slots:
  void on_drop_b_clicked();
  void on_equip_b_clicked();
  void on_cancel_b_clicked();

 private:
  QString getQualityColor(QString quality);
  QFrame *toolTip = nullptr;
  invHex *moveHex = nullptr;
  Item_Info moveInfo = {"", "", "", "", false, false, false, 0, 0};
  bool showToolTip = false;
  bool showMenu = false;
  bool showMoveHex = false;
};

#endif  // INVHEX_H
