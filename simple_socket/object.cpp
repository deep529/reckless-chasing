#include "object.h"
#define SHIFT 20

Object::Object() {
    this->setRect(0,0,50,50);
    this->x_updated = this->x();
    this->y_updated = this->y();
}

Object::~Object() {}

void Object::keyPressEvent(QKeyEvent *event) {
    qDebug() << "keypressed";
    qreal newX = this->x_updated, newY = this->y_updated;

    if (event->key() == Qt::Key_Left) {
        // this->setX(this->x()-SHIFT);
        newX -= SHIFT;
    }
    else if (event->key() == Qt::Key_Right) {
        // this->setX(this->x()+SHIFT);
        newX += SHIFT;
    }
    else if (event->key() == Qt::Key_Up) {
        // this->setY(this->y()-SHIFT);
        newY -= SHIFT;
    }
    else if (event->key() == Qt::Key_Down) {
        // this->setY(this->y()+SHIFT);
        newY += SHIFT;
    }

    this->x_updated = newX;
    this->y_updated = newY;

    emit this->movedTo(newX, newY);
}
