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
#include <stdlib.h>
#include <QFile>
#include <QList>
#include <QWidget>
#include <QPointF>
#include "mythread.h"
#include "myserver.h"
#include "c2spacket.h"
#include "s2cpacket.h"
#include "player.h"
#include <QMutex>

class ServerScreen : public QObject {
    Q_OBJECT
public:
    ServerScreen(QString ip, const quint16 port = 0, int max = 2, QObject *parent = nullptr);
    ~ServerScreen();
    void show();

private:
    void initGame();
    void sendToAll();
    QPointF get_MousePos();
    void fixed_Pos(QPointF center,bool isUp);
    void initialize_pos();

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
    QMutex mutex;
    int player_count = 1;
    int max_players;
    QPointF window_size = QPointF(1050,700);
};


#endif // SERVER_H
