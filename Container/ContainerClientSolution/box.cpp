#include "box.h"
#include "code.h"

Box::Box(): Container(), length{0}, breadth{0}
{
}

Box::Box(int b, int l, int h, int w): Container(h, w), length{l}, breadth{b}
{
    code = Code::getCode("Box");
}

Box::Box(QString c, int b, int l, int h, int w): Container(c, h, w), length{l}, breadth{b}
{
}

void Box::setBreadth(int b)
{
    breadth = b;
}

int Box::getBreadth() const
{
    return breadth;
}

void Box::setLength(int l)
{
    length = l;
}

int Box::getLength() const
{
    return length;
}

int Box::getVolume() const
{
    return (breadth * length * height);
}
