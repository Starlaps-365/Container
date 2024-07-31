#include "pallet.h"
#include "container.h"

Pallet::Pallet() : containers{new QList<Container *>}
{
}

Pallet::~Pallet()
{
    qDeleteAll(containers->begin(), containers->end());
    containers->clear();
}

void Pallet::append(Container *c)
{
    containers->append(c);
}
int Pallet::getTotalWeight() const
{
    int totalWeight{0};
    for (int i=0; i<containers->size(); i++)
    {
        totalWeight += containers->at(i)->getWeight();
    }
    return totalWeight;
}

int Pallet::getTotalVolume() const
{
    int totalVolume{0};
    for (int i=0; i<containers->size(); i++)
    {
        totalVolume += containers->at(i)->getVolume();
    }
    return totalVolume;
}

int Pallet::size() const
{
    return containers->size();
}

Container* Pallet::at(int i)
{
    return containers->at(i);
}
