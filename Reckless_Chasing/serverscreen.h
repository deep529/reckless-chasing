#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QVector>
#include <QSet>
#include <QTimer>
#include "object.h"
#include "mythread.h"
#include "myserver.h"
#include "c2spacket.h"
#include "s2cpacket.h"

class ServerScreen : public QObject {
    Q_OBJECT
public:
    ServerScreen(const quint16 port = 0, int max = 2, QObject *parent = nullptr);
    void show();
    void initGame();
    void sendToAll();

public slots:
    void slotSendToAll();
    void newClient(MyThread *);
    void dataRcvd(C2SPacket cpkt);
    void onClientDisconnect(int);

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    MyServer *server;
    QVector<MyThread*> threads;
    QVector<Object*> players;
    S2CPacket spkt;
    QTimer timer;
    int player_count = 1;
    int max_players;
};


#endif // SERVER_H
