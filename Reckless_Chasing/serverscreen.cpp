#include "serverscreen.h"
#include <QPixmap>

ServerScreen::ServerScreen(QString ip, const quint16 port, int max_players, QObject *parent) : QObject (parent) {
    this->max_players = max_players;

    this->server = new MyServer(this);
    this->server->start(ip, port);
    connect(this->server, SIGNAL(onNewConnection(MyThread*)), this, SLOT(newClient(MyThread*)));

    this->scene = new QGraphicsScene();
    this->view = new QGraphicsView(scene);
    this->scene->setSceneRect(0, 0, 1050, 700);
    this->view->setWindowTitle("Server");
    this->view->setFixedSize(1050, 700);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    QPixmap background(":/images/Backgroung_play.jpg");
    background = background.scaled(this->view->size(), Qt::IgnoreAspectRatio);
    scene->setBackgroundBrush(background);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->scene->setPalette(palette);

    this->players.clear();
}

ServerScreen::~ServerScreen() {
    delete this->server;
    for (int i = 0; i < this->players.size(); i++) {
        delete this->players[i];
    }
    delete this->scene;
    delete this->view;
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

    for (int i = 0; i < this->max_players; i++) {
        if (i == 0) {
            this->players[i]->setPixmap(QPixmap(":/images/police.png"));
        }
        else {
            this->players[i]->setPixmap(QPixmap(":/images/chor.png"));
        }
        this->players[i]->setToolTip("player " + QString::number(i));
        this->players[i]->setX(this->players[i]->initial_pos.x());
        this->players[i]->setY(this->players[i]->initial_pos.y());
        this->scene->addItem(this->players[i]);
    }
}

void ServerScreen::sendToAll() {
    for(int i = 1; i < this->max_players; i++) {
        if (this->spkt.exist[i] && this->players[0]->collidesWithItem(this->players[i])) {
            qDebug() << "--------------------------collision------------------------";

            this->spkt.exist[i] = false;
            this->players[i]->hide();
            this->players[i]->new_x = this->players[0]->new_x;
            this->players[i]->new_y = this->players[0]->new_y;

            this->players[0]->setSpeed(this->players[0]->getSpeed() + SPEED_INCREMENT_AFTER_COLLISION);
        }
    }

    this->mutex.lock();

    int dead = 0;
    for (int i = 1; i < this->max_players; i++) {
        if (!this->spkt.exist[i]) {
            this->players[0]->new_x += this->players[i]->new_x;
            this->players[0]->new_y += this->players[i]->new_y;
            dead++;
        }
    }

    this->players[0]->new_x /= (dead + 1);
    this->players[0]->new_y /= (dead + 1);

    // critical section
    for (int i = 0; i < this->max_players; i++) {
        // update only if player is alive
        if (this->spkt.exist[i]) {
            this->spkt.x[i] = this->players[i]->new_x ;
            this->spkt.y[i] = this->players[i]->new_y ;

            this->players[i]->setX(this->players[i]->new_x + this->players[i]->initial_pos.x());
            this->players[i]->setY(this->players[i]->new_y + this->players[i]->initial_pos.y());
        }
    }

    // qDebug() << "pol :" << this->spkt.x[0] << " " << this->spkt.y[0];

    this->mutex.unlock();

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

        this->players[0]->setSpeed(SERVER_INIT_SPEED);
        this->players[0]->setFlag(QGraphicsItem::ItemIsFocusable);
        this->players[0]->setFocus();
        this->server->stopAccepting();
    }
}

void ServerScreen::dataRcvd(C2SPacket cpkt) {
    this->mutex.lock();

    // critical section
    this->players[cpkt.id]->new_x = cpkt.x;
    this->players[cpkt.id]->new_y = cpkt.y;

    // qDebug() << "chor:" << cpkt.x << " " << cpkt.y;

    this->mutex.unlock();
}

void ServerScreen::onClientDisconnect(int index) {
    exit(0);
}

void ServerScreen::initialize_pos() {
    int count = this->players.size();
    qDebug() << "count:" << count;
    QPointF pos = QPointF(0,0);

    this->players[0]->initial_pos = pos;
    this->players[0]->new_x = pos.x();
    this->players[0]->new_y = pos.y();

    for(int i = 1; i < count; i++) {
        QPointF pos = QPointF(150*i,100*i);
        this->players[i]->initial_pos = pos;
        this->players[i]->new_x = pos.x();
        this->players[i]->new_y = pos.y();
    }
}
