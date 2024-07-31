#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <QObject>
#include <QMap>
#include <QTcpSocket>
class Pallet;

class Serialize : public QObject
{
    Q_OBJECT
public:
    explicit Serialize(QMap<int, Pallet*> *p);

signals:

public slots:
    void doSerialize();

signals:
    void xmlText(QString);
    void linkError(QString msg);
    void finished();

private:
    QMap<int, Pallet*> *pallets;
    QTcpSocket *tcpSocket;
};

#endif // SERIALIZE_H
