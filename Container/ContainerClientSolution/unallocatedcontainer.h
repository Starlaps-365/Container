#ifndef UNALLOCATEDCONTAINER_H
#define UNALLOCATEDCONTAINER_H

#include <QMap>
class Container;
class UnallocatedMemento;

class UnallocatedContainer
{
public:
    UnallocatedContainer();
    ~UnallocatedContainer();
    void insert(QString s, Container *c);
    int size() const;
    Container* take(QString s);
    QString firstKey() const;
    Container* value(QString s);
    void remove(QString s);
    QList<QString> keys() const;
    UnallocatedMemento* createMemento();
    void setMemento(UnallocatedMemento *m);

private:
    QMap<QString, Container*> *containers;
};

#endif // UNALLOCATEDCONTAINER_H
