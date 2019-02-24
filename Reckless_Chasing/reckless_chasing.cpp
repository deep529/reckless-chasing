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
#include <QGraphicsEllipseItem>
#include <QDebug>

#include <QThread>
#include <stdlib.h>
#define steps 10


Reckless_chasing::Reckless_chasing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reckless_chasing)
{
    ui->setupUi(this);

    this->installEventFilter(this);

    this->setFixedSize(900,600);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    QGraphicsScene *scene = new QGraphicsScene();

    Player1->setRect(400,250,100,100);
    scene->addItem(Player1);
    Player1->setFlag(QGraphicsItem::ItemIsFocusable);
    Player1->setFocus();

    QGraphicsView *view = new QGraphicsView(scene);
    view->setWindowTitle("Reckless Chasing(Play)");
    layout->addWidget(view);
    view->show();
    view->setFixedSize(900,600);
    scene->setSceneRect(0,0,900,600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


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
    QPointF window_origin = QPointF(400,250);
    QPointF origin = mapToGlobal(QPoint(0,0));
    QPointF mouse_pos = QCursor::pos();
    mouse_pos -= origin;
    mouse_pos -= window_origin;
    QPointF center = mouse_pos - QPointF(50,50);
    return center;
}

void Reckless_chasing::fixed_Pos(QPointF center, bool isUp)
{

    qreal dy = (center.y() - Player1->y());
    qreal dx = (center.x() - Player1->x());
    dy = (dy / sqrt(pow(dy,2) + pow(dx,2)));
    dx = (dx / sqrt(pow(dy,2) + pow(dx,2)));
    qreal x,y;
    if(isUp)
    {
        x = Player1->x()+(steps * dx);
        y = Player1->y()+(steps * dy);
    }
    else
    {
        x = Player1->x()-(steps * dx);
        y = Player1->y()-(steps * dy);
    }
    if(!((x < -400) || (x > 400) || (y < -250) || (y > 250)))
    {
        if(!(((center.x() - Player1->x())*(center.x() - (Player1->x() + (steps * dx)))) < 0))
        {
            Player1->setX(x);
        }
        if(!(((center.y() - Player1->y())*(center.y() - (Player1->y() + (steps * dy)))) < 0))
        {
            Player1->setY(y);
        }
    }
}

