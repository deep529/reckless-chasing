#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

class player : public QGraphicsRectItem
{
    public :
        player()
        {

        }

        ~player()
        {

        }

        void keyPressEvent(QKeyEvent *event);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

    protected:

    public:

};

#endif // PLAYER_H
