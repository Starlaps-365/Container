#include "toxml.h"
#include <QMetaObject>
#include <QMetaProperty>
#include "container.h"
#include "pallet.h"

ToXML::ToXML()
{
}

QString ToXML::toXmlString(QMap<int, Pallet*> *pallets)
{
    QDomElement root = doc.createElement("pallets");
    root.setAttribute("NumberOfPallets", pallets->size());
    doc.appendChild(root);

    QMapIterator<int, Pallet*> i{*pallets};
    while (i.hasNext())
    {
        i.next();
        int key = i.key();
        Pallet* pallet = i.value();
        QDomElement palletE = doc.createElement("pallet");
        palletE.setAttribute("number", key);
        palletE.setAttribute("weight", pallet->getTotalWeight());
        palletE.setAttribute("volume", pallet->getTotalVolume());
        root.appendChild(palletE);

        for(int p=0; p<pallet->size(); p++)
        {
            const QMetaObject *mo = pallet->at(p)->metaObject();
            QString classname = mo->className();
            QDomElement containerE = doc.createElement(classname);
            palletE.appendChild(containerE);

            for (int i=1; i<mo->propertyCount(); i++)
            {
               QMetaProperty prop = mo->property(i);
               QString propertyName = prop.name();
               QString propertyValue = prop.read(pallet->at(p)).toString();

               QDomElement tagE = doc.createElement(propertyName);
               QDomText text = doc.createTextNode(propertyValue);
               tagE.appendChild(text);
               containerE.appendChild(tagE);
            }
        }
    }
    return doc.toString();
}
