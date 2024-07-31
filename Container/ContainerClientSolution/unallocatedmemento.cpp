#include "unallocatedmemento.h"
#include "unallocatedcontainer.h"

UnallocatedMemento::UnallocatedMemento()
{
}

void UnallocatedMemento::setState(QStringList s)
{
    state = s;
}

QStringList UnallocatedMemento::getState()
{
    return state;
}
