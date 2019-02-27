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
    this->scene->setSceneRect(0,0,800,600);
    this->view->setWindowTitle("Client");
    this->view->setFixedSize(800, 600);
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
    this->socket->read(reinterpret_cast<char*>(this->id), sizeof(this->id));
    disconnect(this->socket, SIGNAL(readyRead()), this, SLOT(idRcvd()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(initObj()));
}

void ClientScreen::initObj() {
    this->socket->read(reinterpret_cast<char*>(&this->spkt), sizeof(this->spkt));

    for (int i = 0; i < this->max_players; i++) {
        this->players.push_back(new Object());
        this->players[i]->setRect(0,0, 50,50);
        this->players[i]->setX(this->spkt.x[i]);
        this->players[i]->setY(this->spkt.y[i]);

        this->players[i]->new_x = this->spkt.x[i];
        this->players[i]->new_y = this->spkt.y[i];

        this->scene->addItem(this->players[i]);
    }

    this->players[this->id]->setFlag(QGraphicsItem::ItemIsFocusable);
    this->players[this->id]->setFocus();

    connect(&this->timer, SIGNAL(timeout()), this, SLOT(sendUpdate()));
    this->timer.start(50);
    disconnect(this->socket, SIGNAL(readyRead()), this, SLOT(initObj()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(dataRcvd()));
}

void ClientScreen::extractData() {
    for (int i = 0; i < this->max_players; i++) {
        this->players[i]->setX(this->spkt.x[i]);
        this->players[i]->setY(this->spkt.y[i]);
    }
}

void ClientScreen::dataRcvd() {
    // qDebug() << "Data rcvd";
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
    this->cpkt.x = this->players[this->id]->new_x;
    this->cpkt.y = this->players[this->id]->new_y;

    this->socket->write(reinterpret_cast<char*>(&(this->cpkt)), sizeof(this->cpkt));
}
