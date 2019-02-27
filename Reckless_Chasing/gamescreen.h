#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <gameserver.h>
#include "object.h"

class GameScreen{

public:
    explicit GameScreen(const bool isServer, QWidget *parent = nullptr);
    ~GameScreen();

    void move(qreal x, qreal y);

    // should be private
    QTcpServer *server;
    QGraphicsView *view;
    QGraphicsScene *scene;
    Object *ob;
};

#endif // SERVERWINDOW_H
