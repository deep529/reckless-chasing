#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QThread>
#include <QTcpSocket>

class GameThread : public QThread {
    Q_OBJECT

public:
    explicit GameThread(const qintptr desc, QObject *parent = nullptr);
    void run();

signals:
    void error(QTcpSocket::SocketError err);

public slots:
    void onRecv();
    void onDisconnect();

private:
    QTcpSocket *socket;
    qintptr socket_descriptor;
};


#endif // GAMETHREAD_H
