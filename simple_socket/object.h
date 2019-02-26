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
    ~Object();

    void keyPressEvent(QKeyEvent *event);

signals:
    void movedTo(qreal x, qreal y);

private:
    qreal x_updated, y_updated;
};


#endif // OBJECT_H
