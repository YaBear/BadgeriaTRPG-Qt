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
  } Item_Info;
  typedef struct Menu_s {
    QFrame *inv_menu = nullptr;
    QPushButton *equip_b = nullptr;
    QPushButton *drop_b = nullptr;
    QPushButton *cancel_b = nullptr;
  } Menu_Inv;

  Item_Info i_info = {"", "", "", "", false, false, false};
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
  bool showToolTip = false;
};

#endif  // INVHEX_H
