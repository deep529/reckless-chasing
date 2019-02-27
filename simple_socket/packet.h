#ifndef PACKET_H
#define PACKET_H

#include <QObject>

enum PacketType {
    FIRST_PACKET,
    NEW_OBJECT,
    NORMAL_PACKET
};

class Packet {
public:
    PacketType type;
    int id;
    qreal x, y;
    Packet();
    Packet(const qreal x, const qreal y);
    ~Packet();
};

static int packet_id = qRegisterMetaType<Packet>("Packet");

#endif // PACKET_H
