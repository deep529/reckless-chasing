#include <QtDebug>
#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerWindow) {
    ui->setupUi(this);

    qDebug() << "initialising server, graphics, scene";
    this->server = new GameServer(4567, this);

    this->scene = new QGraphicsScene(parent);
    this->view = new QGraphicsView(scene);

    this->ob = new Object();
    this->ob->setRect(0,0,50,50);
}

ServerWindow::~ServerWindow() {
    delete ui;
}

