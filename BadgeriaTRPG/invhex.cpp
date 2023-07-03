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
    else if (quality == "Pearlscent")
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
