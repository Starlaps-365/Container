#include "unallocatedcontainer.h"
#include "unallocatedmemento.h"
#include "container.h"
#include "box.h"
#include "cylinder.h"
#include "containerfactory.h"

UnallocatedContainer::UnallocatedContainer(): containers{new QMap<QString, Container*>}
{
}

UnallocatedContainer::~UnallocatedContainer()
{
    qDeleteAll(containers->begin(), containers->end());
    containers->clear();
}

void UnallocatedContainer::insert(QString s, Container *c)
{
    containers->insert(s, c);
}

int UnallocatedContainer::size() const
{
    return containers->size();
}

Container* UnallocatedContainer::take(QString s)
{
    return containers->take(s);
}

QString UnallocatedContainer::firstKey() const
{
    return containers->firstKey();
}

Container* UnallocatedContainer::value(QString s)
{
    return containers->value(s);
}

void UnallocatedContainer::remove(QString s)
{
    containers->remove(s);
}

QList<QString> UnallocatedContainer::keys() const
{
    return containers->keys();
}

UnallocatedMemento* UnallocatedContainer::createMemento()
{
    QStringList data;

    QMapIterator<QString, Container*> i{*containers};
    while (i.hasNext())
    {
        i.next();
        const QMetaObject *mo = i.value()->metaObject();
        if (mo->className() == QString("Box"))
        {
            Box *b = dynamic_cast<Box*>(i.value());
            data << "Box"
                 << b->getCode()
                 << QString::number(b->getBreadth())
                 << QString::number(b->getLength())
                 << QString::number(b->getHeight())
                 << QString::number(b->getWeight());
        }
        if (mo->className() == QString("Cylinder"))
        {
            Cylinder *c = dynamic_cast<Cylinder*>(i.value());
            data << "Cylinder"
                 << c->getCode()
                 << QString::number(c->getDiameter())
                 << QString::number(c->getHeight())
                 << QString::number(c->getWeight());
        }
    }
    UnallocatedMemento *m{new UnallocatedMemento};
    m->setState(data);
    return m;
}

void UnallocatedContainer::setMemento(UnallocatedMemento *m)
{
    containers->clear();
    ContainerFactory cf;
    int values[4];
    QStringList data = m->getState();
    while (!data.isEmpty())
    {
        QString type = data.takeFirst();
        QString code = data.takeFirst();
        if (type == "Box")
            for (int num=0; num<4; num++)
                values[num] = data.takeFirst().toInt();
        if (type == "Cylinder")
            for (int num=0; num<3; num++)
                values[num] = data.takeFirst().toInt();
        Container *c = cf.createContainer(type, code, values);
        containers->insert(c->getCode(), c);
    }
}
