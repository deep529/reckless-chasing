#include "myserver.h"

MyServer::MyServer(QObject *parent) : QTcpServer(parent) {
}

void MyServer::start(const quint16 port) {
    QHostAddress addr;
    addr.setAddress("10.42.0.1");
    if (!this->listen(addr, port)) {
        qDebug() << "Server Class: Server could not start";
        exit(1);
    }
    else {
        qDebug() << "Server Class: Server started";
    }
}

void MyServer::dataAvailabel(const Packet pkt) {
    qDebug() << "Server Class: data availabel";
    emit this->dataRcvd(pkt);
}

void MyServer::incomingConnection(const qintptr socket_descriptor) {
    qDebug() << "Server Class: New Connection " << socket_descriptor;

    MyThread *thread = new MyThread(socket_descriptor, this);
    connect(thread, SIGNAL(dataAvailable(const Packet)), this, SLOT(dataAvailabel(const Packet)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
