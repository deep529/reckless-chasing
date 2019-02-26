#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "object.h"
#include "myserver.h"
#include "packet.h"

class ServerScreen : public QObject {
    Q_OBJECT
public:
    ServerScreen(const quint16 port = 0, QObject *parent = nullptr);
    void show();

public slots:
    void dataRcvd(const Packet pkt);

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    Object *ob;
    MyServer *server;
};


#endif // SERVER_H
