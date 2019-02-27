#include "mythread.h"

MyThread::MyThread(const qintptr desc, QObject *parent) : QThread(parent) {
    this->socket_descriptor = desc;
    this->socket = new QTcpSocket();

    if (!this->socket->setSocketDescriptor(this->socket_descriptor)) {
        emit this->error(this->socket->error());
        return;
    }
}

void MyThread::run() {
    qDebug() << "Thread Class: Starting thread for: " << this->socket_descriptor;

    connect(socket, SIGNAL(readyRead()), this, SLOT(onRecv()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()), Qt::DirectConnection);

    exec();
}

void MyThread::onRecv() {
    // qDebug() << "Thread Class: Data rcvd";
    this->socket->read(reinterpret_cast<char*>(&pkt), sizeof(pkt));

    // qDebug() << "Thread Class: Signal Emited";
    emit this->dataAvailable(pkt);
}

void MyThread::sendPacket(Packet pkt) {
    this->socket->write(reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

void MyThread::onDisconnect() {
    qDebug() << "Thread Class: Disconnecting " << this->socket_descriptor;

    this->socket->deleteLater();
    emit this->exiting(this);
    exit(0);
}
