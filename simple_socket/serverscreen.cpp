#include "serverscreen.h"

ServerScreen::ServerScreen(const quint16 port, QObject *parent) : QObject (parent) {
    this->server = new MyServer(this);
    this->server->start(port);
    connect(this->server, SIGNAL(dataRcvd(const Packet)), this, SLOT(dataRcvd(const Packet)));

    this->scene = new QGraphicsScene();
    this->ob = new Object();
    this->ob->setRect(0,0,50,50);
    this->scene->addItem(this->ob);
    this->view = new QGraphicsView(scene);
    this->view->setWindowTitle("Server");
    this->view->setFixedSize(800, 600);
}

void ServerScreen::show() {
    this->view->show();
}

void ServerScreen::dataRcvd(const Packet pkt) {
    this->ob->setX(pkt.x);
    this->ob->setY(pkt.y);

    qDebug() << "ServerScreen: Rcvd";
}
