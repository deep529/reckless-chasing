#include "player.h"
#define steps 10
#include <QPointF>
#include <iostream>
#include <QPoint>
#include <QCursor>
#include <QRect>
#include <QDebug>

void player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        setPos(x()-steps,y());
        QPointF globalCursorPos = QCursor::pos();
        qDebug() <<globalCursorPos.x()<<" "<<globalCursorPos.y()<<'\n';
    }
    else if(event->key() == Qt::Key_Right)
    {
        setPos(x()+steps,y());
    }
    else if(event->key() == Qt::Key_Up)
    {
        setPos(x(),y()-steps);
    }
    else if(event->key() == Qt::Key_Down)
    {
        setPos(x(),y()+steps);
    }
}

void player::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF offset;
    //std::cout<<"anurag";
    offset = event->pos();
    setPos(offset.x(),offset.y());
    std::cout<<offset.x()<<" "<<offset.y()<<"\n";
}
