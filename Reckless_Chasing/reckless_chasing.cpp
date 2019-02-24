#include "reckless_chasing.h"
#include "ui_reckless_chasing.h"
#include "player.h"
#include <QMessageBox>
#include <QPixmap>
#include <QApplication>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QDebug>
#define steps 10


Reckless_chasing::Reckless_chasing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reckless_chasing)
{
    ui->setupUi(this);

    this->installEventFilter(this);

    this->setFixedSize(900,600);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(scene);
    view->setWindowTitle("Reckless Chasing(Play)");
    layout->addWidget(view);
    view->show();
    view->setFixedSize(900,600);
    scene->setSceneRect(0,0,900,600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

Reckless_chasing::~Reckless_chasing()
{
    delete ui;
}

