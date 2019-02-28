#ifndef C2SPACKET_H
#define C2SPACKET_H

#include <QObject>

class C2SPacket {
public:
    C2SPacket();
    C2SPacket(const qreal x, const qreal y);
    ~C2SPacket();

    int id;
    qreal x, y;
};

static int c2spacket_id = qRegisterMetaType<C2SPacket>("C2SPacket");

#endif // C2SPACKET_H
