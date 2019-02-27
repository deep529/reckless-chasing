#include "reckless_chasing.h"
#include "ui_reckless_chasing.h"
#include "player.h"
#include <QMessageBox>
#include <QPixmap>
#include <qmath.h>
#include <QApplication>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QThread>
#include <stdlib.h>
#include <QFile>
#include <QList>
#include <iostream>
#define steps 10

Reckless_chasing::Reckless_chasing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reckless_chasing)
{
    ui->setupUi(this);

    this->installEventFilter(this);

    window_size = QPointF(900,600);

    this->setFixedSize(window_size.x(),window_size.y());

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(Player);
    Player->setFlag(QGraphicsItem::ItemIsFocusable);
    Player->setFocus();
    QGraphicsView *view = new QGraphicsView(scene);
    view->setWindowTitle("Reckless Chasing(Play)");
    layout->addWidget(view);
    view->show();
    view->setFixedSize(window_size.x(),window_size.y());
    scene->setSceneRect(0,0,window_size.x(),window_size.y());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   for(int i = 0; i < 3; i++)
   {
       player *temp = new player();
       Other_player.push_back(temp);
   }

   initialize_pos();

   for(int i = 0; i < 3; i++)
   {
       Other_player[i]->setRect(Other_player[i]->initial_pos.x(),Other_player[i]->initial_pos.y(),Other_player[i]->radius * 2,Other_player[i]->radius * 2);
       scene->addItem(Other_player[i]);
   }

   Player->setRect(Player->initial_pos.x(),Player->initial_pos.y(),Player->radius * 2,Player->radius * 2);

   pressedKeys.clear();
}

Reckless_chasing::~Reckless_chasing()
{
    delete ui;
}

bool Reckless_chasing::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyRelease) {
        pressedKeys.remove(((QKeyEvent*)event)->key());
    }
    else if (event->type() == QEvent::KeyPress) {
        pressedKeys.insert(((QKeyEvent*)event)->key());


        if((pressedKeys.contains(Qt::Key_W))&&(pressedKeys.contains(Qt::Key_S)))
        {
            //Do  nothing
        }
        else if(pressedKeys.contains(Qt::Key_W))
        {
            QPointF center = get_MousePos();
            fixed_Pos(center,true);
        }
        else if(pressedKeys.contains(Qt::Key_S))
        {
            QPointF center = get_MousePos();
            fixed_Pos(center,false);
        }
    }
    return false;
}

QPointF Reckless_chasing::get_MousePos()
{
    QPointF window_origin = QPointF(Player->initial_pos.x(),Player->initial_pos.y());
    QPointF origin = mapToGlobal(QPoint(0,0));
    QPointF mouse_pos = QCursor::pos();
    mouse_pos -= origin;
    mouse_pos -= window_origin;
    QPointF center = mouse_pos - QPointF(Player->radius,Player->radius);
    return center;
}

void Reckless_chasing::fixed_Pos(QPointF center, bool isUp)
{

    qreal dy = (center.y() - Player->y());
    qreal dx = (center.x() - Player->x());
    dy = (dy / sqrt(pow(dy,2) + pow(dx,2)));
    dx = (dx / sqrt(pow(dy,2) + pow(dx,2)));
    qreal x,y;
    if(isUp)
    {
        x = Player->x()+(steps * dx);
        y = Player->y()+(steps * dy);
    }
    else
    {
        x = Player->x()-(steps * dx);
        y = Player->y()-(steps * dy);
    }
    if(!is_boundary_crossed(x,y,Player->initial_pos.x(),Player->initial_pos.y()))
    {
        if(!(((center.x() - Player->x())*(center.x() - (Player->x() + (steps * dx)))) < 0))
        {
            Player->setX(x);
        }
        else {
            Player->setX(center.x());
        }
        if(!(((center.y() - Player->y())*(center.y() - (Player->y() + (steps * dy)))) < 0))
        {
            Player->setY(y);
        }
        else {
            Player->setY(center.y());
        }
    }
    else {
        if(x < -(Player->initial_pos.x()))
        {
            Player->setX(-(Player->initial_pos.x()));
        }
        if(x > (window_size.x() - Player->initial_pos.x() - (2 * Player->radius)))
        {
            Player->setX(window_size.x() - Player->initial_pos.x() - (2 * Player->radius));
        }
        if(y > (window_size.y() - Player->initial_pos.y() - (2 * Player->radius)))
        {
            Player->setY(window_size.y() - Player->initial_pos.y() - (2 * Player->radius));
        }
        if(y < -(Player->initial_pos.y()))
        {
            Player->setY(-(Player->initial_pos.y()));
        }
    }
    Player->iscolliding(Other_player[0],0);
    Player->iscolliding(Other_player[1],1);
    Player->iscolliding(Other_player[2],2);
}

void Reckless_chasing::initialize_pos()
{
    int count = Other_player.size() + 1;
    QPointF pos = QPointF(0,0);
    int gap_x = ((window_size.x() - (count * 2 * Other_player[0]->radius))) / (count - 1);
    int gap_y = ((window_size.y() - (count * 2 * Other_player[0]->radius))) / (count - 1);
    Player->initial_pos = pos;
    for(int i = 0; i < (count - 1); i++)
    {
        pos = pos + QPointF(gap_x,gap_y) + QPointF(2 * Other_player[0]->radius,2 * Other_player[0]->radius);
        Other_player[i]->initial_pos = pos;
    }
}

bool Reckless_chasing::is_boundary_crossed(double x, double y,double initialx, double initialy)
{
    return ((x < -initialx) || (x > (window_size.x() - initialx - (2 * Player->radius))) || (y > (window_size.y() - initialy - (2 * Player->radius))) || (y < -initialy));
}


