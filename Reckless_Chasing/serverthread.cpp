#include "gamethread.h"

#include <QtDebug>

GameThread::GameThread(const qintptr desc, QObject *parent) : QThread(parent) {
    this->socket_descriptor = desc;
}

void GameThread::run() {
    qDebug() << "Starting thread for: " << this->socket_descriptor;

    this->socket = new QTcpSocket();

    if (!this->socket->setSocketDescriptor(this->socket_descriptor)) {
        emit this->error(this->socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(onRecv()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()), Qt::DirectConnection);

    exec();
}

void GameThread::onRecv() {
    QByteArray data = this->socket->readAll();

    qDebug() << "data: " << data;
}

void GameThread::onDisconnect() {
    qDebug() << "Disconnecting " << this->socket_descriptor;

    this->socket->deleteLater();
    exit(0);
}
