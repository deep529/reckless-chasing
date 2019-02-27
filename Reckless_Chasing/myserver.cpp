#include "myserver.h"

MyServer::MyServer(QObject *parent) : QTcpServer(parent) {}

void MyServer::start(const QString ip, const quint16 port) {
    QHostAddress addr;
    addr.setAddress(ip);
    if (!this->listen(addr, port)) {
        qDebug() << "Server Class: Server could not start";
        exit(1);
    }
    else {
        qDebug() << "Server Class: Server started";
    }
}

void MyServer::incomingConnection(const qintptr socket_descriptor) {
    qDebug() << "Server Class: New Connection " << socket_descriptor;

    MyThread *thread = new MyThread(socket_descriptor, this);
    connect(thread, SIGNAL(dataAvailable(C2SPacket)), this->parent(), SLOT(dataRcvd(C2SPacket)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    emit this->onNewConnection(thread);
    thread->start();
}