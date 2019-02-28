#include "clientscreen.h"
#define steps 10

ClientScreen::ClientScreen(QString ip, const quint16 port, int max_players, QObject *parent) : QObject(parent) {
    this->max_players = max_players;

    this->socket = new QTcpSocket(this);
    this->socket->connectToHost(ip, port);

    connect(this->socket, SIGNAL(connected()), this,  SLOT(onConnection()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(idRcvd()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));

    this->scene = new QGraphicsScene();
    this->view = new QGraphicsView(scene);
    this->scene->setSceneRect(0,0,900,600);
    this->view->setWindowTitle("Client");
    this->view->setFixedSize(900, 600);
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
        this->players[i]->setRect(0,0, this->players[i]->radius * 2, this->players[i]->radius * 2);
        this->players[i]->setX(this->spkt.x[i]);
        this->players[i]->setY(this->spkt.y[i]);

        this->players[i]->new_x = this->spkt.x[i];
        this->players[i]->new_y = this->spkt.y[i];

        this->scene->addItem(this->players[i]);
    }

    this->players[this->id]->setFlag(QGraphicsItem::ItemIsFocusable);
    this->players[this->id]->setFocus();

    connect(&this->timer, SIGNAL(timeout()), this, SLOT(sendUpdate()));
    this->timer.start(20);
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

bool ClientScreen::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyRelease) {
        pressedKeys.remove(((QKeyEvent*)event)->key());
    }
    else if (event->type() == QEvent::KeyPress) {
        pressedKeys.insert(((QKeyEvent*)event)->key());


        if((pressedKeys.contains(Qt::Key_W))&&(pressedKeys.contains(Qt::Key_S))){
            //Do  nothing
        }
        else if(pressedKeys.contains(Qt::Key_W)) {
            QPointF center = get_MousePos();
            fixed_Pos(center,true);
        }
        else if(pressedKeys.contains(Qt::Key_S)) {
            QPointF center = get_MousePos();
            fixed_Pos(center,false);
        }
    }
    return false;
}


QPointF ClientScreen::get_MousePos() {
    QPointF window_origin = QPointF(this->players[this->id]->initial_pos.x(),this->players[this->id]->initial_pos.y());
    QPointF origin = this->view->mapToGlobal(QPoint(0,0));

    QPointF mouse_pos = QCursor::pos();
    mouse_pos -= origin;
    mouse_pos -= window_origin;
    QPointF center = mouse_pos - QPointF(this->players[this->id]->radius,this->players[this->id]->radius);
    return center;
}

void ClientScreen::fixed_Pos(QPointF center, bool isUp) {
    qreal dy = (center.y() - this->players[this->id]->new_y);
    qreal dx = (center.x() - this->players[this->id]->new_x);
    dy = (dy / sqrt(pow(dy,2) + pow(dx,2)));
    dx = (dx / sqrt(pow(dy,2) + pow(dx,2)));
    qreal x,y;

    if(isUp) {
        x = this->players[this->id]->new_x + (steps * dx);
        y = this->players[this->id]->new_y + (steps * dy);
    }
    else {
        x = this->players[this->id]->new_x - (steps * dx);
        y = this->players[this->id]->new_y - (steps * dy);
    }

    if(!is_boundary_crossed(x,y,this->players[this->id]->initial_pos.x(),this->players[this->id]->initial_pos.y())) {
        if(!(((center.x() - this->players[this->id]->new_x)*(center.x() - (this->players[this->id]->new_x + (steps * dx)))) < this->id)) {
            this->players[this->id]->new_x = x;
        }
        else {
            this->players[this->id]->new_x = center.x();
        }
        if(!(((center.y() - this->players[this->id]->new_y)*(center.y() - (this->players[this->id]->new_y + (steps * dy)))) < this->id)) {
            this->players[this->id]->new_y = y;
        }
        else {
            this->players[this->id]->new_y = center.y();
        }
    }
    else {
        if(x < -(this->players[this->id]->initial_pos.x()))
        {
            this->players[this->id]->setX(-(this->players[this->id]->initial_pos.x()));
        }
        if(x > (window_size.x() - this->players[this->id]->initial_pos.x() - (2 * this->players[this->id]->radius)))
        {
            this->players[this->id]->setX(window_size.x() - this->players[this->id]->initial_pos.x() - (2 * this->players[this->id]->radius));
        }
        if(y > (window_size.y() - this->players[this->id]->initial_pos.y() - (2 * this->players[this->id]->radius)))
        {
            this->players[this->id]->setY(window_size.y() - this->players[this->id]->initial_pos.y() - (2 * this->players[this->id]->radius));
        }
        if(y < -(this->players[this->id]->initial_pos.y()))
        {
            this->players[this->id]->setY(-(this->players[this->id]->initial_pos.y()));
        }
    }

    for (int i = 1; i < this->max_players; i++) {
        this->players[this->id]->iscolliding(this->players[i], i);
    }
}


bool ClientScreen::is_boundary_crossed(double x, double y,double initialx, double initialy) {
    return ((x < -initialx) || (x > (window_size.x() - initialx - (2 * this->players[0]->radius))) || (y > (window_size.y() - initialy - (2 * this->players[0]->radius))) || (y < -initialy));
}

