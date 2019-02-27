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
    int id;
    Object();
    ~Object();

    void set_updated_values(qreal x, qreal y);
    void keyPressEvent(QKeyEvent *event);

signals:
    void movedTo(qreal x, qreal y);

public:
    qreal x_updated, y_updated;
};


#endif // OBJECT_H
