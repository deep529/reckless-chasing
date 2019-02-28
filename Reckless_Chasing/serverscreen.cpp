#include "serverscreen.h"
#define steps 10

ServerScreen::ServerScreen(QString ip, const quint16 port, int max_players, QObject *parent) : QObject (parent) {
    this->max_players = max_players;
    this->installEventFilter(this);

    this->server = new MyServer(this);
    this->server->start(ip, port);
    connect(this->server, SIGNAL(onNewConnection(MyThread*)), this, SLOT(newClient(MyThread*)));

    this->scene = new QGraphicsScene();
    this->view = new QGraphicsView(scene);
    this->scene->setSceneRect(0,0,900,600);
    this->view->setWindowTitle("Server");
    this->view->setFixedSize(900,600);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

    for(int i = 0; i < this->max_players; i++) {
        this->players[i]->setRect(this->players[i]->initial_pos.x(), this->players[i]->initial_pos.y(), this->players[i]->radius * 2, this->players[i]->radius * 2);
        this->scene->addItem(this->players[i]);
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
        this->timer.start(30);

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

bool ServerScreen::eventFilter(QObject *obj, QEvent *event) {
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


QPointF ServerScreen::get_MousePos() {
    QPointF window_origin = QPointF(this->players[0]->initial_pos.x(),this->players[0]->initial_pos.y());
    QPointF origin = this->view->mapToGlobal(QPoint(0,0));

    QPointF mouse_pos = QCursor::pos();
    mouse_pos -= origin;
    mouse_pos -= window_origin;
    QPointF center = mouse_pos - QPointF(this->players[0]->radius,this->players[0]->radius);
    return center;
}

void ServerScreen::fixed_Pos(QPointF center, bool isUp) {
    qreal dy = (center.y() - this->players[0]->new_y);
    qreal dx = (center.x() - this->players[0]->new_x);
    dy = (dy / sqrt(pow(dy,2) + pow(dx,2)));
    dx = (dx / sqrt(pow(dy,2) + pow(dx,2)));
    qreal x,y;

    if(isUp) {
        x = this->players[0]->new_x + (steps * dx);
        y = this->players[0]->new_y + (steps * dy);
    }
    else {
        x = this->players[0]->new_x - (steps * dx);
        y = this->players[0]->new_y - (steps * dy);
    }

    if(!is_boundary_crossed(x,y,this->players[0]->initial_pos.x(),this->players[0]->initial_pos.y())) {
        if(!(((center.x() - this->players[0]->new_x)*(center.x() - (this->players[0]->new_x + (steps * dx)))) < 0)) {
            this->players[0]->new_x = x;
        }
        else {
            this->players[0]->new_x = center.x();
        }
        if(!(((center.y() - this->players[0]->new_y)*(center.y() - (this->players[0]->new_y + (steps * dy)))) < 0)) {
            this->players[0]->new_y = y;
        }
        else {
            this->players[0]->new_y = center.y();
        }
    }
    else {
        if(x < -(this->players[0]->initial_pos.x()))
        {
            this->players[0]->setX(-(this->players[0]->initial_pos.x()));
        }
        if(x > (window_size.x() - this->players[0]->initial_pos.x() - (2 * this->players[0]->radius)))
        {
            this->players[0]->setX(window_size.x() - this->players[0]->initial_pos.x() - (2 * this->players[0]->radius));
        }
        if(y > (window_size.y() - this->players[0]->initial_pos.y() - (2 * this->players[0]->radius)))
        {
            this->players[0]->setY(window_size.y() - this->players[0]->initial_pos.y() - (2 * this->players[0]->radius));
        }
        if(y < -(this->players[0]->initial_pos.y()))
        {
            this->players[0]->setY(-(this->players[0]->initial_pos.y()));
        }
    }

    for (int i = 1; i < this->max_players; i++) {
        this->players[0]->iscolliding(this->players[i], i);
    }
}


bool ServerScreen::is_boundary_crossed(double x, double y,double initialx, double initialy) {
    return ((x < -initialx) || (x > (window_size.x() - initialx - (2 * this->players[0]->radius))) || (y > (window_size.y() - initialy - (2 * this->players[0]->radius))) || (y < -initialy));
}

void ServerScreen::initialize_pos() {
    int count = this->players.size();
    QPointF pos = QPointF(0,0);
    int gap_x = int(window_size.x() - (count * 2 * this->players[0]->radius)) / (count - 1);
    int gap_y = int(window_size.y() - (count * 2 * this->players[0]->radius)) / (count - 1);

    this->players[0]->initial_pos = pos;

    for(int i = 1; i < count; i++) {
        pos = pos + QPointF(gap_x,gap_y) + QPointF(2 * this->players[0]->radius,2 * this->players[0]->radius);
        this->players[i]->initial_pos = pos;
        this->players[i]->new_x = pos.x();
        this->players[i]->new_y = pos.y();
    }
}
