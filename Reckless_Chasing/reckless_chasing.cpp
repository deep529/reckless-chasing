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
    Player1->setRect(400,250,100,100);
    scene->addItem(Player1);
    Player1->setFlag(QGraphicsItem::ItemIsFocusable);
    Player1->setFocus();
    QGraphicsView *view = new QGraphicsView(scene);
    view->setWindowTitle("Reckless Chasing(Play)");
    layout->addWidget(view);
    view->show();
    view->setFixedSize(900,600);
    scene->setSceneRect(0,0,900,600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pressedKeys.clear();
}

Reckless_chasing::~Reckless_chasing()
{
    delete ui;
}

bool Reckless_chasing::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyRelease) {
        qDebug() <<"Released "<< (char) ((QKeyEvent*)event)->key();

        pressedKeys.remove(((QKeyEvent*)event)->key());

        qreal x = Player1->x();
        qreal y = Player1->y();
        qreal up = y - steps;
        qreal down = y + steps;
        qreal left = x - steps;
        qreal right = x + steps;

        if (pressedKeys.contains(Qt::Key_A))
        {
            Player1->setPos(left, y);
            x = left;
        }

        if (pressedKeys.contains(Qt::Key_W))
        {
            Player1->setPos(x, up);
            y = up;
        }

        if (pressedKeys.contains(Qt::Key_D))
        {
            Player1->setPos(right, y);
            x = right;
        }

        if (pressedKeys.contains(Qt::Key_S))
        {
            Player1->setPos(x, down);
            y = down;
        }
    }
    else if (event->type() == QEvent::KeyPress) {
        qDebug() <<"Pressed "<< (char) ((QKeyEvent*)event)->key();

        pressedKeys.insert(((QKeyEvent*)event)->key());

        qreal x = Player1->x();
        qreal y = Player1->y();
        qreal up = y - steps;
        qreal down = y + steps;
        qreal left = x - steps;
        qreal right = x + steps;

        if (pressedKeys.contains(Qt::Key_A))
        {
            Player1->setPos(left, y);
        }

        if (pressedKeys.contains(Qt::Key_W))
        {
            Player1->setPos(x, up);
        }

        if (pressedKeys.contains(Qt::Key_D))
        {
            Player1->setPos(right, y);
        }

        if (pressedKeys.contains(Qt::Key_S))
        {
            Player1->setPos(x, down);
        }
    }
    return false;
}

