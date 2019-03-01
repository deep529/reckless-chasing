#include "clientscreen.h"

ClientScreen::ClientScreen(QString ip, const quint16 port, int max_players, QObject *parent) : QObject(parent) {
    this->max_players = max_players;

    this->socket = new QTcpSocket(this);
    this->socket->connectToHost(ip, port);

    connect(this->socket, SIGNAL(connected()), this,  SLOT(onConnection()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(idRcvd()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));

    this->scene = new QGraphicsScene();
    this->view = new QGraphicsView(scene);
    this->scene->setSceneRect(0, 0, 1050, 700);
    this->view->setWindowTitle("Client");
    this->view->setFixedSize(1050, 700);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->socket->waitForConnected();
}

void ClientScreen::show() {
    this->view->show();
}

void ClientScreen::onConnection() {
    qDebug() << "Socket connected";
}

void ClientScreen::idRcvd() {
    char c;
    this->socket->read(&c, sizeof(c));
    this->id = int(c-'0');

    disconnect(this->socket, SIGNAL(readyRead()), this, SLOT(idRcvd()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(initObj()));
}

void ClientScreen::initObj() {
    this->socket->read(reinterpret_cast<char*>(&this->spkt), sizeof(this->spkt));

    for (int i = 0; i < this->max_players; i++) {
        this->players.push_back(new Player());
        this->players[i]->initial_pos = QPointF(this->spkt.x[i], this->spkt.y[i]);
        //this->players[i]->setRect(0,0, this->players[i]->radius * 2, this->players[i]->radius * 2);
        if (i == 0) {
            this->players[i]->setPixmap(QPixmap(":/images/police.png"));
        }
        else if (i == this->id) {
            this->players[i]->setPixmap(QPixmap(":/images/chor.png"));
        }
        else {
            this->players[i]->setPixmap(QPixmap(":/images/black_chor.png"));
        }

        this->players[i]->setX(this->spkt.x[i]);
        this->players[i]->setY(this->spkt.y[i]);

        this->players[i]->new_x = this->spkt.x[i];
        this->players[i]->new_y = this->spkt.y[i];

        this->scene->addItem(this->players[i]);
    }

    this->players[this->id]->setSpeed(CLIENT_INIT_SPEED);
    this->players[this->id]->setFlag(QGraphicsItem::ItemIsFocusable);
    this->players[this->id]->setFocus();

    connect(&this->timer, SIGNAL(timeout()), this, SLOT(sendUpdate()));
    this->timer.start(100);
    disconnect(this->socket, SIGNAL(readyRead()), this, SLOT(initObj()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(dataRcvd()));
}

void ClientScreen::extractData() {
    for (int i = 0; i < this->max_players; i++) {
        this->players[i]->setX(this->spkt.x[i] + this->players[i]->initial_pos.x());
        this->players[i]->setY(this->spkt.y[i] + this->players[i]->initial_pos.y());

        if (this->spkt.exist[i] == false) {
            this->players[i]->hide();

            if (i == this->id) {
                this->players[this->id]->clearFocus();
                this->players[0]->setFlag(QGraphicsItem::ItemIsFocusable);
                this->players[0]->setFocus();
                this->players[0]->setSpeed(SPEED_AFTER_COLLISION);
                this->players[0]->new_x = this->players[0]->x();
                this->players[0]->new_y = this->players[0]->y();
            }
        }
    }
}

void ClientScreen::dataRcvd() {
    this->socket->read(reinterpret_cast<char*>(&this->spkt), sizeof(this->spkt));
    this->extractData();
}

void ClientScreen::onDisconnect() {
    qDebug() << "Disconnected";
    this->socket->close();
    this->deleteLater();
}

void ClientScreen::sendUpdate() {
    this->cpkt.id = this->id;

    if (this->spkt.exist[this->id]) {
        this->cpkt.x = this->players[this->id]->new_x;
        this->cpkt.y = this->players[this->id]->new_y;
    }
    else {
        this->cpkt.x = this->players[0]->new_x;
        this->cpkt.y = this->players[0]->new_y;
    }

    this->socket->write(reinterpret_cast<char*>(&(this->cpkt)), sizeof(this->cpkt));
}
