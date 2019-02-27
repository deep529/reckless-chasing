#include "serverscreen.h"

ServerScreen::ServerScreen(const quint16 port, QObject *parent) : QObject (parent) {
    this->server = new MyServer(this);
    this->server->start(port);
    connect(this->server, SIGNAL(dataRcvd(Packet)), this, SLOT(dataRcvd(Packet)));
    connect(this->server, SIGNAL(onNewConnection(MyThread*)), this, SLOT(newClient(MyThread*)));

    this->ob = new Object();
    this->ob->setFlag(QGraphicsItem::ItemIsFocusable);
    this->ob->setFocus();
    this->ob->setRect(100,100,50,50);

    this->scene = new QGraphicsScene();
    this->scene->addItem(this->ob);
    this->view = new QGraphicsView(scene);
    this->scene->setSceneRect(0,0,800,600);
    this->view->setWindowTitle("Server");
    this->view->setFixedSize(800, 600);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(&this->timer, SIGNAL(timeout()), this, SLOT(notify()));
    this->timer.start(50);
}

void ServerScreen::show() {
    this->view->show();
}

void ServerScreen::sendToAllThreads(Packet pkt) {
    for (QSet<MyThread*>::iterator itr = this->threads.begin(); itr != this->threads.end(); itr++) {
        (*itr)->sendPacket(pkt);
    }
}

void ServerScreen::dataRcvd(Packet pkt) {
    this->other_ob->setX(pkt.x);
    this->other_ob->setY(pkt.y);
    // qDebug() << "Rcvd: " << pkt.x << pkt.y;
    this->sendToAllThreads(pkt);
}

void ServerScreen::newClient(MyThread *thread) {
    this->other_ob = new Object();
    int x = rand() % 800, y = rand() % 600;
    qDebug() << "new: " << x << " " << y;

    this->other_ob->setRect(qreal(x), qreal(y), 50, 50);
    this->scene->addItem(this->other_ob);

    this->pkt.x = x;
    this->pkt.y = y;
    this->pkt.id = 1;
    this->pkt.type = FIRST_PACKET;
    thread->id = 1;
    thread->sendPacket(this->pkt);

    this->pkt.x = this->ob->x();
    this->pkt.y = this->ob->y();
    this->pkt.id = 0;
    this->pkt.type = NEW_OBJECT;
    thread->sendPacket(this->pkt);

    this->threads.insert(thread);
    connect(thread, SIGNAL(exiting(MyThread*)), this, SLOT(clientExited(MyThread*)));
}

void ServerScreen::clientExited(MyThread *thread) {
    delete this->other_ob;
    this->threads.remove(thread);
}

void ServerScreen::notify() {
    Packet packet;
    packet.x = this->ob->x_updated;
    packet.y = this->ob->y_updated;
    packet.id = 0;
    packet.type = NORMAL_PACKET;

    this->sendToAllThreads(pkt);

    this->ob->setX(packet.x);
    this->ob->setY(packet.y);
}
