#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

class Player : public QGraphicsEllipseItem
{
public :
    qreal radius = 50;
    QPointF initial_pos = QPointF(400,250);

    Player();
    ~Player();

    bool iscolliding(Player *player, int i);

protected:

public:
    qreal new_x, new_y;

};

#endif // PLAYER_H
