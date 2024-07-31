#ifndef CONTAINERFACTORY_H
#define CONTAINERFACTORY_H

class QString;
class Container;

class ContainerFactory
{
public:
    ContainerFactory();
    Container* createContainer(QString type, int data[4]);
    Container* createContainer(QString type, QString code, int data[4]);
};


#endif // CONTAINERFACTORY_H
