#include "invhex.h"

invHex::invHex(QWidget *parent) : QFrame(parent) {
    // Constructor implementation
    setMouseTracking(true);
}

QString invHex::getQualityColor(QString quality) {
    QString temp = nullptr;

    if (quality == "Poor")
        temp = "#A9A9A9";
    else if (quality == "Uncommon")
        temp = "#008000";
    else if (quality == "Rare")
        temp = "#00008B";
    else if (quality == "Epic")
        temp = "#800080";
    else if (quality == "Legendary")
        temp = "#FFA500";
    else if (quality == "Pearlescent")
        temp = "#00FFFF";

    return temp;
}

void invHex::on_drop_b_clicked() {
    //    qDebug() << "Drop!";
    this->i_info.info = "";
    this->i_info.exist = false;
    this->i_info.name = "";
    this->i_info.quality = "";
    this->i_info.type = "";
    this->setStyleSheet("");
    showMenu = false;
    delete (i_menu.drop_b);
    delete (i_menu.equip_b);
    delete (i_menu.inv_menu);
}

void invHex::on_equip_b_clicked() {
    //    qDebug() << "Equip!";
}

void invHex::on_cancel_b_clicked() {
    //    qDebug() << "Cancel!";
    showMenu = false;
    delete (i_menu.drop_b);
    delete (i_menu.equip_b);
    delete (i_menu.inv_menu);
}

// Наведение мышкой на ячейки ивентаря
bool invHex::event(QEvent *event) {
    if (event->type() == QEvent::Enter && !showToolTip && i_info.exist &&
        !showMenu && !showMoveHex) {
        toolTip = new QFrame();
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QPointF pos = mouseEvent->globalPosition();
        toolTip->setWindowFlags(Qt::ToolTip);
        toolTip->setGeometry(pos.x() + 20, pos.y() + 20, 150, 150);
        toolTip->setFrameShape(QFrame::Box);
        toolTip->setStyleSheet(
            "QFrame {background-color: rgb(13, 45, 61); color: white; }");
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
    } else if (event->type() == QEvent::Leave && i_info.exist && showToolTip) {
        delete (toolTip);
        showToolTip = false;
        //            qDebug() << "Hover Leave";
    }
    return QWidget::event(event);
}

//void invHex::mouseMoveEvent(QMouseEvent *event)
//{
//    QPointF pos1 = event->globalPosition();
//    if (i_info.exist && !showMenu && !showMoveHex) {
//        toolTip->setGeometry(pos1.x() + 20, pos1.y() + 20, 150, 150);
//        //            qDebug() << "Hover Move" << pos1;
//    }
//    if (showMoveHex) {
//        QWidget *widget = QApplication::widgetAt(event->globalPos());
//        if (widget && widget->underMouse())
//        {
//            invHex *temp = qobject_cast<invHex *>(widget);
//            if (temp) {
//                qDebug() << temp->i_info.x << " " << temp->i_info.y;
//            }
//        }
//        moveHex->setGeometry(pos1.x() + 15, pos1.y() + 15, 35, 35);
//    }
//    if (event->buttons() & Qt::LeftButton)
//    {
////        qDebug() << "Current mouse position:" << event->pos();
//    }

//}

//void invHex::mousePressEvent(QMouseEvent *event)
//{
//    QPointF pos = event->globalPosition();
//    if (event->buttons() == Qt::RightButton && i_info.exist &&
//        !showMenu) {

//        i_menu.inv_menu = new QFrame();
//        i_menu.inv_menu->setWindowFlags(Qt::SplashScreen);
//        i_menu.inv_menu->setGeometry(pos.x() + 20, pos.y() + 20, 150, 100);
//        i_menu.inv_menu->setFrameShape(QFrame::Box);

//        i_menu.equip_b = new QPushButton(i_menu.inv_menu);
//        connect(i_menu.equip_b, SIGNAL(clicked()), this,
//                SLOT(on_equip_b_clicked()));
//        setup_menu_button(i_menu.equip_b, 0, 0, 150, 30, "Надеть");
//        if (!i_info.equipable) i_menu.equip_b->setDisabled(true);

//        i_menu.drop_b = new QPushButton(i_menu.inv_menu);
//        connect(i_menu.drop_b, SIGNAL(clicked()), this,
//                SLOT(on_drop_b_clicked()));
//        setup_menu_button(i_menu.drop_b, 0, 35, 150, 30, "Выбросить");

//        i_menu.cancel_b = new QPushButton(i_menu.inv_menu);
//        connect(i_menu.cancel_b, SIGNAL(clicked()), this,
//                SLOT(on_cancel_b_clicked()));
//        setup_menu_button(i_menu.cancel_b, 0, 70, 150, 30, "Закрыть");

//        i_menu.inv_menu->show();
//        showMenu = true;
//    } else if (event->buttons() == Qt::LeftButton && i_info.exist &&
//               !showMenu) {
//        if (showToolTip) {
//            delete (toolTip);
//            showToolTip = false;
//        }
//        moveHex = new invHex();
//        setup_move(moveHex, pos);
//    }
//}

//void invHex::mouseReleaseEvent(QMouseEvent *event)
//{
////    qDebug() << i_info.x << "+" << i_info.y;
//    if (showMoveHex) {
//        delete (moveHex);
//        showMoveHex = false;
//    }
//    QPoint cursorPos = QCursor::pos();
//    qDebug() << cursorPos;
//    QWidget *widget = QApplication::widgetAt(cursorPos);
//    if (widget && widget->underMouse())
//    {
//        invHex *temp = qobject_cast<invHex *>(widget);
//        if (temp) {
//            qDebug() << temp->i_info.x << " " << temp->i_info.y;
//        }
//    }
//}

void invHex::setup_menu_button(QPushButton *button, int x, int y, int w, int h, QString name) {
    button->setText(name);
    button->setGeometry(x, y, w, h);
    button->show();
}

void invHex::setup_move(invHex *moveHex, QPointF pos) {
    moveHex->i_info = i_info;
    moveHex->setGeometry(pos.x() + 15, pos.y() + 15, 35, 35);
    moveHex->setWindowFlags(Qt::SplashScreen);
    moveHex->setFrameShape(QFrame::Panel);
    moveHex->setFrameShadow(QFrame::Raised);
    moveHex->setStyleSheet(this->styleSheet());
    showMoveHex = true;
    moveHex->showMoveHex = true;
    moveHex->show();
}
