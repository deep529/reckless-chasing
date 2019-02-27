#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include "mythread.h"

class MyServer : public QTcpServer {
    Q_OBJECT

public:
    explicit MyServer(QObject *parent = nullptr);
    void start(const QString ip, const quint16 port);

signals:
    void onNewConnection(MyThread *thread);

public slots:

protected:
    void incomingConnection(const qintptr socket_descriptor);
};

#endif // MYSERVER_H
