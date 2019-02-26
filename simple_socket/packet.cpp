#include "packet.h"

Packet::Packet() {}

Packet::Packet(const qreal x, const qreal y) {
    this->x = x;
    this->y = y;
}

Packet::~Packet() {}
