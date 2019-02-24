#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsEllipseItem>
#include <QKeyEvent>

class Object : public QGraphicsEllipseItem {
public:
    Object();
    ~Object();

    void keyPressEvent(QKeyEvent *event);
};


#endif // OBJECT_H
