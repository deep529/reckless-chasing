#include <QtDebug>
#include "gamescreen.h"
#include "gameserver.h"

GameScreen::GameScreen(const bool isServer, QWidget *parent) {

    qDebug() << "initialising server, graphics, scene";

    this->scene = new QGraphicsScene(parent);
    this->view = new QGraphicsView(scene);

    if (isServer) {
        this->ob = new Object();
        this->scene->addItem(this->ob);
        this->server = new GameServer(4567);
    }
    else {
        this->ob = new Object(4567);
        this->scene->addItem(this->ob);
        this->ob->setFlag(QGraphicsItem::ItemIsFocusable);
        this->ob->setFocus();
    }

    this->ob->setRect(0,0,50,50);
}

GameScreen::~GameScreen() {
    delete this->server;
}

void GameScreen::move(qreal x, qreal y) {
    this->ob->setX(x);
    this->ob->setY(y);
}
