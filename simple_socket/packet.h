#ifndef PACKET_H
#define PACKET_H

#include <QObject>

class Packet {
public:
    qreal x, y;
    Packet();
    Packet(const qreal x, const qreal y);
    ~Packet();
};

static int packet_id = qRegisterMetaType<Packet>("Packet");

#endif // PACKET_H
