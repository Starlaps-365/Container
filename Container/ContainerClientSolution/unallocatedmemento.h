#ifndef UNALLOCATEDMEMENTO_H
#define UNALLOCATEDMEMENTO_H

#include <QStringList>
class UnallocatedContainer;

class UnallocatedMemento
{
private:
    friend class UnallocatedContainer;
    UnallocatedMemento();
    void setState(QStringList s);
    QStringList getState();
    QStringList state;
};

#endif // UNALLOCATEDMEMENTO_H
