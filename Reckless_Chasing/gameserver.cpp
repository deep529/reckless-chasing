#include "gameserver.h"
#include "gamethread.h"

GameServer::GameServer(const quint16 port, QObject *parent) : QTcpServer(parent) {
    if (!this->listen(QHostAddress::Any, port)) {
        qDebug() << "Server could not start";
        exit(1);
    }
    else {
        qDebug() << "Server started";
    }
}

void GameServer::incomingConnection(const qintptr socket_descriptor) {
    qDebug() << "New Connection " << socket_descriptor;

    GameThread *thread = new GameThread(socket_descriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
