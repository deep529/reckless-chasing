#include "object.h"
#define SHIFT 5

Object::Object() {}

void Object::keyPressEvent(QKeyEvent *event) {
    // qDebug() << "keypressed";

    if (event->key() == Qt::Key_Left) {
        // this->setX(this->x()-SHIFT);
        this->new_x -= SHIFT;
    }
    else if (event->key() == Qt::Key_Right) {
        // this->setX(this->x()+SHIFT);
        this->new_x += SHIFT;
    }
    else if (event->key() == Qt::Key_Up) {
        // this->setY(this->y()-SHIFT);
        this->new_y -= SHIFT;
    }
    else if (event->key() == Qt::Key_Down) {
        // this->setY(this->y()+SHIFT);
        this->new_y += SHIFT;
    }

    // emit this->movedTo(newX, newY);
}
