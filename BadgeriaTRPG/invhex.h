#ifndef INVHEX_H
#define INVHEX_H

#include <QFrame>
#include <QMouseEvent>

#include "mainwindow.h"

class invHex : public QFrame
{
    Q_OBJECT

public:
    explicit invHex(QWidget *parent = nullptr);
    bool event(QEvent *event) override;

private:
    QFrame *toolTip = nullptr;
    bool showToolTip = false;
    bool cursorInsideTooltip = false;
};

#endif // INVHEX_H
