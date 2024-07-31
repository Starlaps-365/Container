#include "code.h"
#include <QDate>
#include <QString>

int Code::count{0};

Code::Code()
{}

QString Code::getCode(QString type)
{
    QDate today = QDate::currentDate();
    QString year = QString::number(today.year());
    QString month;
    if (today.month()<10)
        month = QString("0") + QString::number(today.month());
    else
        month = QString::number(today.month());
    QString t = (type=="Box")?"B":"C";
    QString c = QString::number(++count);
    return (year + "/" + month + "/" + t + c);
}
