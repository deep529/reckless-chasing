#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QTcpSocket>
#include <QString>
#include <QDebug>

class Object : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    Object();

    // void keyPressEvent(QKeyEvent *event);

public:
    qreal new_x, new_y;
};


#endif // OBJECT_H
