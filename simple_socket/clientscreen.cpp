#include "clientscreen.h"

ClientScreen::ClientScreen(const quint16 port, QObject *parent) : QObject(parent) {
    this->socket = new QTcpSocket(this);
    this->socket->connectToHost("10.42.0.1", port);

    connect(this->socket, SIGNAL(connected()), this,  SLOT(onConnection()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(dataRcvd()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));

    this->ob = new Object();
    this->ob->setRect(0,0,50,50);
    this->ob->setFlag(QGraphicsItem::ItemIsFocusable);
    this->ob->setFocus();
    connect(this->ob, SIGNAL(movedTo(qreal, qreal)), this, SLOT(onMove(qreal, qreal)));

    this->scene = new QGraphicsScene();
    this->scene->addItem(this->ob);
    this->view = new QGraphicsView(scene);
    this->view->setWindowTitle("Client");
    this->view->setFixedSize(800, 600);
}

void ClientScreen::show() {
    this->view->show();
}

void ClientScreen::sendPosition(qreal x, qreal y) {
    pkt.x = x;
    pkt.y = y;

    qDebug() << "sent " << x << y;
    this->socket->write(reinterpret_cast<char*>(&(this->pkt)), sizeof(this->pkt));
    this->socket->flush();
}

void ClientScreen::onMove(qreal x, qreal y) {
    this->sendPosition(x, y);
}

void ClientScreen::onConnection() {
    qDebug() << "Socket connected";
    this->sendPosition(this->ob->x(), this->ob->y());
}

void ClientScreen::dataRcvd() {
    qDebug() << "Data rcvd";
    this->socket->read(reinterpret_cast<char*>(&pkt), sizeof(pkt));
    this->ob->setX(pkt.x);
    this->ob->setY(pkt.y);
}

void ClientScreen::onDisconnect() {
    qDebug() << "Disconnected";
    this->socket->close();
    this->deleteLater();
}
