#include "object.h"
#define SHIFT 10

Object::Object() {
    this->setRect(0,0,50,50);
    this->x_updated = this->x();
    this->y_updated = this->y();
}

Object::~Object() {}

void Object::set_updated_values(qreal x, qreal y) {
    this->x_updated = x;
    this->y_updated = y;
}

void Object::keyPressEvent(QKeyEvent *event) {
    // qDebug() << "keypressed";

    if (event->key() == Qt::Key_Left) {
        // this->setX(this->x()-SHIFT);
        this->x_updated -= SHIFT;
    }
    else if (event->key() == Qt::Key_Right) {
        // this->setX(this->x()+SHIFT);
        this->x_updated += SHIFT;
    }
    else if (event->key() == Qt::Key_Up) {
        // this->setY(this->y()-SHIFT);
        this->y_updated -= SHIFT;
    }
    else if (event->key() == Qt::Key_Down) {
        // this->setY(this->y()+SHIFT);
        this->y_updated += SHIFT;
    }

    // emit this->movedTo(newX, newY);
}
