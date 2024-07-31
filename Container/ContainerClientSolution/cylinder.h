#ifndef CYLINDER_H
#define CYLINDER_H

#include "container.h"

class Cylinder : public Container
{
    Q_OBJECT
    Q_PROPERTY(int diameter READ getDiameter WRITE setDiameter)

public:
    Cylinder();
    Cylinder(int d, int h, int w);
    Cylinder(QString c, int d, int h, int w);
    void setDiameter(int d);
    int getDiameter() const;
    int getVolume() const;

private:
    int diameter;
};

#endif // CYLINDER_H
