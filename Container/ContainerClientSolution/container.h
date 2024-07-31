#ifndef CONTAINER_H
#define CONTAINER_H

#include <QObject>

class Container: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString code READ getCode)
    Q_PROPERTY(int height READ getHeight WRITE setHeight)
    Q_PROPERTY(int weight READ getWeight WRITE setWeight)

public:
    Container();
    Container(int h, int w);
    Container(QString c, int h, int w);
    QString getCode() const;
    void setHeight(int h);
    int getHeight() const;
    void setWeight(int w);
    int getWeight() const;
    virtual int getVolume() const = 0;

protected:
    QString code;
    int height;
    int weight;
};

#endif // CONTAINER_H
