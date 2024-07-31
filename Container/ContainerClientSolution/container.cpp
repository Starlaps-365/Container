#include "container.h"

Container::Container(): code{"0"}, height{0}, weight{0}
{
}

Container::Container(int h, int w): code{"***"}, height{h}, weight{w}
{
}

Container::Container(QString c, int h, int w): code{c}, height{h}, weight{w}
{
}

void Container::setHeight(int h)
{
    height = h;
}

int Container::getHeight() const
{
    return height;
}

void Container::setWeight(int w)
{
    weight = w;
}

int Container::getWeight() const
{
    return weight;
}

QString Container::getCode() const
{
    return code;
}
