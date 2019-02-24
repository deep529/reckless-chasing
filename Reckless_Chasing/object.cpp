#include "object.h"
#define SHIFT 20

Object::Object() {
    this->setRect(0,0,100,100);
}

Object::~Object() {}

void Object::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        this->setX(this->x()-SHIFT);
    }
    else if (event->key() == Qt::Key_Right) {
        this->setX(this->x()+SHIFT);
    }
    else if (event->key() == Qt::Key_Up) {
        this->setY(this->y()-SHIFT);
    }
    else if (event->key() == Qt::Key_Down) {
        this->setY(this->y()+SHIFT);
    }
}
