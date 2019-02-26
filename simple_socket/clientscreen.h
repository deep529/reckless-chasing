#ifndef CLIENTSCREEN_H
#define CLIENTSCREEN_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "object.h"
#include "myserver.h"
#include "packet.h"

class ClientScreen : public QObject {
    Q_OBJECT
public:
    ClientScreen(const quint16 port, QObject *parent = nullptr);
    void show();
    void sendPosition(qreal x, qreal y);

private slots:
    void onMove(qreal x, qreal y);
    void onConnection();
    void dataRcvd();
    void onDisconnect();

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    Object *ob;
    QTcpSocket *socket;
    Packet pkt;
};

#endif // CLIENTSCREEN_H
