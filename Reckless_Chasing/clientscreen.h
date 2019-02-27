#ifndef CLIENTSCREEN_H
#define CLIENTSCREEN_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>
#include <QTimer>
#include <QVector>
#include "object.h"
#include "myserver.h"

class ClientScreen : public QObject {
    Q_OBJECT
public:
    ClientScreen(QString ip, const quint16 port, int max_player, QObject *parent = nullptr);
    void show();
    void extractData();

private slots:
    void onConnection();
    void idRcvd();
    void initObj();
    void dataRcvd();
    void onDisconnect();
    void sendUpdate();

private:
    int id;
    QGraphicsView *view;
    QGraphicsScene *scene;
    Object *ob;
    Object *other_ob;
    QTcpSocket *socket;
    QTimer timer;
    S2CPacket spkt;
    C2SPacket cpkt;
    QVector<Object*> players;
    int max_players = 2;
};

#endif // CLIENTSCREEN_H
