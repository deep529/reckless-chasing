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
#include <QMessageBox>
#include <QPixmap>
#include <qmath.h>
#include <QApplication>
#include <QVBoxLayout>
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QThread>
#include <stdlib.h>
#include <QFile>
#include <QList>
#include <QWidget>
#include <QPointF>
// #include "object.h"
#include "mythread.h"
#include "myserver.h"
#include "c2spacket.h"
#include "s2cpacket.h"
#include "player.h"

class ServerScreen : public QObject {
    Q_OBJECT

public:
    ServerScreen(QString ip, const quint16 port = 0, int max = 2, QObject *parent = nullptr);
    void show();
    void initGame();
    void sendToAll();

    QPointF get_MousePos();
    void fixed_Pos(QPointF center, bool isUp);

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
    QVector<Player*> players;
    S2CPacket spkt;
    QTimer timer;
    int player_count = 1;
    int max_players;
    QPointF window_size = QPointF(900, 600);

    void initialize_pos();
};


#endif // SERVER_H
