#ifndef INVHEX_H
#define INVHEX_H

#include <QFrame>
#include <QMouseEvent>

#include "mainwindow.h"

class invHex : public QFrame
{
    Q_OBJECT

public:
    typedef struct Info_s {
        QString name;
        QString quality;
        QString type;
        QString info;
    } Item_Info;

    Item_Info i_info = {"", "", "", ""};
    explicit invHex(QWidget *parent = nullptr);
    bool event(QEvent *event) override;

private:
    QString getQualityColor(QString quality);
    QFrame *toolTip = nullptr;
    bool showToolTip = false;
    bool cursorInsideTooltip = false;
};

#endif // INVHEX_H
