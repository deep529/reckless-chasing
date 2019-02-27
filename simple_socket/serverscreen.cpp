#include "serverscreen.h"

ServerScreen::ServerScreen(const quint16 port, int max_players, QObject *parent) : QObject (parent) {
    this->max_players = max_players;

    this->server = new MyServer(this);
    this->server->start(port);
    connect(this->server, SIGNAL(onNewConnection(MyThread*)), this, SLOT(newClient(MyThread*)));

    this->scene = new QGraphicsScene();
    this->view = new QGraphicsView(scene);
    this->scene->setSceneRect(0,0,800,600);
    this->view->setFixedSize(800,600);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ServerScreen::show() {
    this->view->show();
}

void ServerScreen::initGame() {
    qDebug() << "Game init";
    for (int i = 0; i < this->max_players; i++) {
        this->players.push_back(new Object());
        this->players[i]->setRect(0,0, 50,50);
        this->players[i]->setX(100*i);
        this->players[i]->setY(100*i);
        this->scene->addItem(this->players[i]);
    }
}

void ServerScreen::sendToAll() {
    for (int i = 0; i < this->max_players; i++) {
        /*if (this->players[i]->new_x < 0) {
            // this->players[i]->new_x = 0+50;
        }
        else if (this->players[i]->new_x > 800) {
            // this->players[i]->new_x = 800-50;
        }

        if (this->players[i]->new_y < 0) {
            // this->players[i]->new_y = 0+50;
        }
        else if (this->players[i]->new_y > 800) {
            // this->players[i]->new_y = 800-50;
        }*/


        this->spkt.x[i] = this->players[i]->new_x;
        this->spkt.y[i] = this->players[i]->new_y;

        this->players[i]->setX(this->players[i]->new_x);
        this->players[i]->setY(this->players[i]->new_y);
    }

    for (int i = 0; i < this->threads.size(); i++) {
        this->threads[i]->sendPacket(this->spkt);
    }
}

void ServerScreen::slotSendToAll() {
    this->sendToAll();
}

void ServerScreen::newClient(MyThread *thread) {
    thread->sendInt(player_count);
    thread->id = player_count;
    player_count++;

    this->threads.push_back(thread);
    connect(thread, SIGNAL(exiting(int)), this, SLOT(onClientDisconnect(int)));

    if (this->player_count == this->max_players) {
        this->initGame();
        this->sendToAll();
        connect(&(this->timer), SIGNAL(timeout()), this, SLOT(slotSendToAll()));
        this->timer.start(100);

        this->players[0]->setFlag(QGraphicsItem::ItemIsFocusable);
        this->players[0]->setFocus();
    }
}

void ServerScreen::dataRcvd(C2SPacket cpkt) {
    this->players[cpkt.id]->new_x = cpkt.x;
    this->players[cpkt.id]->new_y = cpkt.y;
}

void ServerScreen::onClientDisconnect(int index) {
    exit(0);
}
