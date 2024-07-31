#ifndef PALLET_H
#define PALLET_H

#include <QList>
class Container;

class Pallet
{
public:
    Pallet();
    ~Pallet();
    int getTotalWeight() const;
    int getTotalVolume() const;
    void append(Container *c);
    int size() const;
    Container* at(int i);

private:
    QList<Container *> *containers;
};

#endif // PALLET_H
