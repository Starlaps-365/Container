#include "cylinder.h"
#include <QtMath>
#include "code.h"

Cylinder::Cylinder(): Container (), diameter{0}
{
}

Cylinder::Cylinder(int d, int h, int w): Container(h, w), diameter{d}
{
    code = Code::getCode("Cylinder");
}

Cylinder::Cylinder(QString c, int d, int h, int w): Container(c, h, w), diameter{d}
{
}

void Cylinder::setDiameter(int d)
{
    diameter = d;
}

int Cylinder::getDiameter() const
{
    return diameter;
}

int Cylinder::getVolume() const
{
    return static_cast<int>(M_PI * qPow(diameter/2.0, 2) * height);

}
