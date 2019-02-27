#include "clientscreen.h"

ClientScreen::ClientScreen(const quint16 port, QObject *parent) : QObject(parent) {
    this->socket = new QTcpSocket(this);
    this->socket->connectToHost("10.42.0.1", port);

    connect(this->socket, SIGNAL(connected()), this,  SLOT(onConnection()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(dataRcvd()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));

    this->ob = new Object();
    this->ob->setFlag(QGraphicsItem::ItemIsFocusable);
    this->ob->setFocus();

    this->scene = new QGraphicsScene();
    this->scene->addItem(this->ob);
    this->view = new QGraphicsView(scene);
    this->scene->setSceneRect(0,0,800,600);
    this->view->setWindowTitle("Client");
    this->view->setFixedSize(800, 600);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->socket->waitForConnected();

    connect(&this->timer, SIGNAL(timeout()), this, SLOT(sendUpdate()));
    this->timer.start(50);
}

void ClientScreen::show() {
    this->view->show();
}

void ClientScreen::sendPosition(qreal x, qreal y) {
    this->pkt.x = x;
    this->pkt.y = y;
    this->pkt.type = NORMAL_PACKET;
    this->pkt.id = this->ob->id;

    // qDebug() << "sent " << x << y;
    this->socket->write(reinterpret_cast<char*>(&(this->pkt)), sizeof(this->pkt));
    // this->socket->flush();
}

void ClientScreen::onConnection() {
    qDebug() << "Socket connected";
}

void ClientScreen::dataRcvd() {
    // qDebug() << "Data rcvd";
    this->socket->read(reinterpret_cast<char*>(&this->rcv_pkt), sizeof(this->rcv_pkt));

    if (this->rcv_pkt.type == FIRST_PACKET) {
        this->ob->id = this->rcv_pkt.id;
        this->ob->setX(this->rcv_pkt.x);
        this->ob->setY(this->rcv_pkt.y);
    }
    else if (this->rcv_pkt.type == NEW_OBJECT) {
        this->other_ob = new Object();
        this->other_ob->id = this->rcv_pkt.id;
        this->other_ob->setX(this->rcv_pkt.x);
        this->other_ob->setY(this->rcv_pkt.y);
        this->scene->addItem(this->other_ob);
    }
    else if (this->rcv_pkt.type == NORMAL_PACKET) {
        if (this->rcv_pkt.id == 0) {
            this->other_ob->setX(this->rcv_pkt.x);
            this->other_ob->setY(this->rcv_pkt.y);
        }
        else {
            this->ob->setX(this->rcv_pkt.x);
            this->ob->setY(this->rcv_pkt.y);
        }
    }
}

void ClientScreen::onDisconnect() {
    qDebug() << "Disconnected";
    this->socket->close();
    this->deleteLater();
}

void ClientScreen::sendUpdate() {
    this->sendPosition(this->ob->x_updated, this->ob->y_updated);
}
