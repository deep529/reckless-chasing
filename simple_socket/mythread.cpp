#include "mythread.h"

MyThread::MyThread(const qintptr desc, QObject *parent) : QThread(parent) {
    this->socket_descriptor = desc;
}

void MyThread::run() {
    qDebug() << "Thread Class: Starting thread for: " << this->socket_descriptor;

    this->socket = new QTcpSocket();

    if (!this->socket->setSocketDescriptor(this->socket_descriptor)) {
        emit this->error(this->socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(onRecv()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()), Qt::DirectConnection);

    exec();
}

void MyThread::onRecv() {
    qDebug() << "Thread Class: Data rcvd";

    this->socket->read(reinterpret_cast<char*>(&pkt), sizeof(pkt));

    qDebug() << "Thread Class: Signal Emited";
    emit this->dataAvailable(pkt);

    this->socket->write(reinterpret_cast<char*>(&pkt), sizeof(pkt));
    this->socket->flush();
}

void MyThread::onDisconnect() {
    qDebug() << "Thread Class: Disconnecting " << this->socket_descriptor;

    this->socket->deleteLater();
    exit(0);
}
