#ifndef TOXML_H
#define TOXML_H

#include <QDomDocument>
#include <QMap>
class Pallet;

class ToXML
{
public:
    ToXML();
    QString toXmlString(QMap<int, Pallet*> *pallets);
private:
    QDomDocument doc;
};

#endif // TOXML_H
