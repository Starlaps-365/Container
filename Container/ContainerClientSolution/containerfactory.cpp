#include "containerfactory.h"
#include "box.h"
#include "cylinder.h"
#include <QString>

ContainerFactory::ContainerFactory()
{
}

Container* ContainerFactory::createContainer(QString type, int data[4])
{
    if(type == "BoxButton" || type == "Box")
        return new Box(data[0], data[1], data[2], data[3]);
    else if(type == "CylinderButton" || type == "Cylinder")
        return new Cylinder(data[0], data[1], data[2]);
    return nullptr;
}

Container* ContainerFactory::createContainer(QString type, QString code, int data[4])
{
    if(type == "BoxButton" || type == "Box")
        return new Box(code, data[0], data[1], data[2], data[3]);
    else if(type == "CylinderButton" || type == "Cylinder")
        return new Cylinder(code, data[0], data[1], data[2]);
    return nullptr;
}
