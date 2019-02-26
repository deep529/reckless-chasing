#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include "mythread.h"
#include "packet.h"

class MyServer : public QTcpServer {
    Q_OBJECT

public:
    explicit MyServer(QObject *parent = nullptr);
    void start(const quint16 port);

signals:
    void dataRcvd(const Packet pkt);

public slots:
    void dataAvailabel(const Packet pkt);

protected:
    void incomingConnection(const qintptr socket_descriptor);
};

#endif // MYSERVER_H
