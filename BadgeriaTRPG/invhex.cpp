#include "invhex.h"

invHex::invHex(QWidget *parent) : QFrame(parent)
{
    // Constructor implementation
    setMouseTracking(true);
}

QString invHex::getQualityColor(QString quality)
{
    QString temp = nullptr;

    if (quality == "Poor")
        temp = "#A9A9A9";
    else if (quality == "Uncommon")
        temp = "#008000";
    else if (quality == "Rare")
        temp = "#0000FF";
    else if (quality == "Epic")
        temp = "#800080";
    else if (quality == "Legendary")
        temp = "#FFA500";
    else if (quality == "Pearlscent")
        temp = "#00FFFF";

    return temp;
}
