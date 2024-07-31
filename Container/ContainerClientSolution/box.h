#ifndef BOX_H
#define BOX_H

#include "container.h"

class Box : public Container
{
    Q_OBJECT
    Q_PROPERTY(int length READ getLength WRITE setLength)
    Q_PROPERTY(int breadth READ getBreadth WRITE setBreadth)

public:
    Box();
    Box(int b, int l, int h, int w);
    Box(QString code, int b, int l, int h, int w);
    void setBreadth(int b);
    int getBreadth() const;
    void setLength(int l);
    int getLength() const;
    int getVolume() const;

private:
    int length;
    int breadth;
};


#endif // BOX_H
