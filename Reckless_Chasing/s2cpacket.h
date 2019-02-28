#ifndef S2CPACKET_H
#define S2CPACKET_H

#include <QObject>

class S2CPacket {
public:
    S2CPacket();
    qreal x[4];
    qreal y[4];
    bool exist[4];
};

static int s2cpacket_id = qRegisterMetaType<S2CPacket>("S2CPacket");

#endif  // S2CPACKET_H
