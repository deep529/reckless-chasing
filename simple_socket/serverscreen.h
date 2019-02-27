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
#include "packet.h"

class ServerScreen : public QObject {
    Q_OBJECT
public:
    ServerScreen(const quint16 port = 0, QObject *parent = nullptr);
    void show();
    void sendToAllThreads(Packet pkt);

signals:
    void sendToClient(Packet);

public slots:
    void dataRcvd(Packet pkt);
    void newClient(MyThread *thread);
    void clientExited(MyThread*);
    void notify();

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    Object *ob;
    Object *other_ob;
    MyServer *server;
    Packet pkt;
    QSet<MyThread*> threads;
    QTimer timer;
};


#endif // SERVER_H
