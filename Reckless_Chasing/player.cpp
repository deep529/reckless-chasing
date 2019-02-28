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

Player::Player() {}

Player::~Player() {}

bool Player::iscolliding(Player *player,int i) {

    if(QGraphicsItem::collidesWithItem(player)) {
        qDebug() <<"Colliding with "<<i+1<<'\n';
    }

    return false;
}
