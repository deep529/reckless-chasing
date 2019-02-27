#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

class player : public QGraphicsEllipseItem
{
public :
    qreal radius = 50;
    QPointF initial_pos = QPointF(400,250);

    player()
    {

    }

    ~player()
    {

    }

protected:

public:

};

#endif // PLAYER_H
