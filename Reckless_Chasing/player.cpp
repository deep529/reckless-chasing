#include "player.h"
#define steps 50
#include <QPointF>
#include <iostream>
#include <QPoint>
#include <QCursor>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <math.h>
#include <QWidget>


bool player::iscolliding(player *Player,int i)
{

    if(QGraphicsItem::collidesWithItem(Player))
    {
        qDebug() <<"Colliding with "<<i+1<<'\n';
    }
}
