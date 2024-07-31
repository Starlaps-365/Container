#include "serialize.h"
#include "toxml.h"
#include "pallet.h"

Serialize::Serialize(QMap<int, Pallet*> *p) : pallets{p}, tcpSocket{nullptr}
{
}

void Serialize::doSerialize()
{
    QTcpSocket *tcpSocket{new QTcpSocket(this)};
    tcpSocket->connectToHost("127.0.0.1", 6164);
    if (tcpSocket->waitForConnected())
    {
        ToXML toXml;
        QString string = toXml.toXmlString(pallets);
        emit xmlText(string);

        tcpSocket->write(string.toLatin1());
        tcpSocket->waitForBytesWritten(10000);
        tcpSocket->close();
    }
    else
    {
        emit linkError("Could not connect to host");
    }
    emit finished();
}
