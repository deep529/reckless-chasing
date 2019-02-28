#include "serverscreen.h"

ServerScreen::ServerScreen(QString ip, const quint16 port, int max_players, QObject *parent) : QObject(parent) {
    this->max_players = max_players;

    this->server = new MyServer(this);
    this->server->start(ip, port);
    connect(this->server, SIGNAL(onNewConnection(MyThread*)), this, SLOT(newClient(MyThread*)));

    this->scene = new QGraphicsScene();
    this->view = new QGraphicsView(scene);
    this->scene->setSceneRect(0, 0, 900, 600);
    this->view->setWindowTitle("Server");
    this->view->setFixedSize(900, 600);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->players.clear();
}

void ServerScreen::show() {
    this->view->show();
}

void ServerScreen::initGame() {
    qDebug() << "Game init";
    for (int i = 0; i < this->max_players; i++) {
        this->players.push_back(new Player());
    }

    this->initialize_pos();

    qDebug() << this->max_players;
    for (int i = 0; i < this->max_players; i++) {
        this->players[i]->setRect(0, 0, this->players[i]->radius * 2, this->players[i]->radius * 2);
        this->players[i]->setX(this->players[i]->initial_pos.x());
        this->players[i]->setY(this->players[i]->initial_pos.y());
        this->scene->addItem(this->players[i]);
        qDebug() << "Added p" << i;
    }
}

void ServerScreen::sendToAll() {
    for (int i = 0; i < this->max_players; i++) {
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
        this->timer.start(40);

        this->players[0]->setFlag(QGraphicsItem::ItemIsFocusable);
        this->players[0]->setFocus();
        this->server->stopAccepting();
    }
}

void ServerScreen::dataRcvd(C2SPacket cpkt) {
    this->players[cpkt.id]->new_x = cpkt.x;
    this->players[cpkt.id]->new_y = cpkt.y;
}

void ServerScreen::onClientDisconnect(int index) {
    exit(0);
}

void ServerScreen::initialize_pos() {
    int count = this->players.size();
    qDebug() << "count:" << count;
    QPointF pos = QPointF(0, 0);

    int gap_x = int(window_size.x() - (count * 2 * this->players[0]->radius)) / (count - 1);
    int gap_y = int(window_size.y() - (count * 2 * this->players[0]->radius)) / (count - 1);

    this->players[0]->initial_pos = pos;
    this->players[0]->new_x = pos.x();
    this->players[0]->new_y = pos.y();

    for (int i = 1; i < count; i++) {
        pos = pos + QPointF(gap_x, gap_y) + QPointF(2 * this->players[i]->radius, 2 * this->players[i]->radius);
        pos = QPointF(0, 0);
        this->players[i]->initial_pos = pos;
        this->players[i]->new_x = pos.x();
        this->players[i]->new_y = pos.y();
    }
}
