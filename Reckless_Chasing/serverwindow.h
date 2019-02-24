#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <gameserver.h>
#include "object.h"

namespace Ui {
    class ServerWindow;
}

class ServerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    Ui::ServerWindow *ui;

    GameServer *server;
    QGraphicsView *view;
    QGraphicsScene *scene;
    Object *ob;
};

#endif // SERVERWINDOW_H
