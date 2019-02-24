#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QTcpServer>

class GameServer : public QTcpServer {
    Q_OBJECT

public:
    explicit GameServer(const quint16 port = 0, QObject *parent = nullptr);

protected:
    void incomingConnection(const qintptr socket_descriptor);
};

#endif // GAMESERVER_H
