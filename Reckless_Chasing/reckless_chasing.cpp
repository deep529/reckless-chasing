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


player *Player1 = new player();

Reckless_chasing::Reckless_chasing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reckless_chasing)
{
    ui->setupUi(this);

    this->installEventFilter(this);
    //setMouseTracking(true);

   QPixmap background(":/images/Images/Play_Background.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(50);
    QGraphicsScene *scene = new QGraphicsScene();
    //player *Player1 = new player();
    Player1->setRect(500,200,100,100);
    scene->addItem(Player1);
    Player1->setFlag(QGraphicsItem::ItemIsFocusable);
    Player1->setFocus();
    QGraphicsView *view = new QGraphicsView(scene);
    //view->setMouseTracking(true);
    view->setWindowTitle("Reckless Chasing(Play)");
    layout->addWidget(view);
    view->show();
    view->setFixedSize(1100,600);
    scene->setSceneRect(0,0,1100,600);
}

Reckless_chasing::~Reckless_chasing()
{
    delete ui;
}

bool Reckless_chasing::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type()==QEvent::KeyPress) {

            pressedKeys += ((QKeyEvent*)event)->key();

            qreal x = Player1->x();
            qreal y = Player1->y();
            qreal up = y - steps;
            qreal down = y + steps;
            qreal left = x - steps;
            qreal right = x + steps;

            if( (pressedKeys.contains(Qt::Key_A)) && !(pressedKeys.contains(Qt::Key_S)) && !(pressedKeys.contains(Qt::Key_D)) && !(pressedKeys.contains(Qt::Key_W)) )  //1
            {
                 Player1->setPos(left,y);
            }
            else if( (pressedKeys.contains(Qt::Key_S)) && !(pressedKeys.contains(Qt::Key_A)) && !(pressedKeys.contains(Qt::Key_D)) && !(pressedKeys.contains(Qt::Key_W)) )
            {
                Player1->setPos(x,down);
            }
            else if( (pressedKeys.contains(Qt::Key_D)) && !(pressedKeys.contains(Qt::Key_A)) && !(pressedKeys.contains(Qt::Key_S)) && !(pressedKeys.contains(Qt::Key_W)) )
            {
                Player1->setPos(right,y);
            }
            else if( (pressedKeys.contains(Qt::Key_W)) && !(pressedKeys.contains(Qt::Key_A)) && !(pressedKeys.contains(Qt::Key_D)) && !(pressedKeys.contains(Qt::Key_S)) )
            {
                Player1->setPos(x,up);
            }
            else if( (pressedKeys.contains(Qt::Key_A)) && (pressedKeys.contains(Qt::Key_S)) && !(pressedKeys.contains(Qt::Key_D)) && !(pressedKeys.contains(Qt::Key_W)) )  //1
            {
                 Player1->setPos(left,down);
            }
            else if( (pressedKeys.contains(Qt::Key_A)) && (pressedKeys.contains(Qt::Key_D)) && !(pressedKeys.contains(Qt::Key_S)) && !(pressedKeys.contains(Qt::Key_W)) )  //1
            {
                 Player1->setPos(x,y);
            }
            else if( (pressedKeys.contains(Qt::Key_A)) && (pressedKeys.contains(Qt::Key_W)) && !(pressedKeys.contains(Qt::Key_D)) && !(pressedKeys.contains(Qt::Key_S)) )  //1
            {
                 Player1->setPos(left,up);
            }
            else if( (pressedKeys.contains(Qt::Key_D)) && (pressedKeys.contains(Qt::Key_S)) && !(pressedKeys.contains(Qt::Key_A)) && !(pressedKeys.contains(Qt::Key_W)) )  //1
            {
                 Player1->setPos(right,down);
            }
            else if( (pressedKeys.contains(Qt::Key_D)) && (pressedKeys.contains(Qt::Key_W)) && !(pressedKeys.contains(Qt::Key_A)) && !(pressedKeys.contains(Qt::Key_S)) )  //1
            {
                 Player1->setPos(right,up);
            }
            else if( (pressedKeys.contains(Qt::Key_W)) && (pressedKeys.contains(Qt::Key_S)) && !(pressedKeys.contains(Qt::Key_D)) && !(pressedKeys.contains(Qt::Key_A)) )  //1
            {
                 Player1->setPos(x,y);
            }
            else if( (pressedKeys.contains(Qt::Key_A)) && (pressedKeys.contains(Qt::Key_S)) && (pressedKeys.contains(Qt::Key_D)) && !(pressedKeys.contains(Qt::Key_W)) )  //1
            {
                 Player1->setPos(x,down);
            }
            else if( (pressedKeys.contains(Qt::Key_A)) && (pressedKeys.contains(Qt::Key_S)) && (pressedKeys.contains(Qt::Key_W)) && !(pressedKeys.contains(Qt::Key_D)) )  //1
            {
                 Player1->setPos(left,y);
            }
            else if( (pressedKeys.contains(Qt::Key_A)) && (pressedKeys.contains(Qt::Key_D)) && (pressedKeys.contains(Qt::Key_W)) && !(pressedKeys.contains(Qt::Key_S)) )  //1
            {
                 Player1->setPos(x,up);
            }
            else if( (pressedKeys.contains(Qt::Key_D)) && (pressedKeys.contains(Qt::Key_S)) && (pressedKeys.contains(Qt::Key_W)) && !(pressedKeys.contains(Qt::Key_A)) )  //1
            {
                 Player1->setPos(right,y);
            }
            else if( (pressedKeys.contains(Qt::Key_W)) && (pressedKeys.contains(Qt::Key_S)) && (pressedKeys.contains(Qt::Key_D)) && (pressedKeys.contains(Qt::Key_A)) )  //1
            {
                 Player1->setPos(x,y);
            }
            else if( !(pressedKeys.contains(Qt::Key_W)) && !(pressedKeys.contains(Qt::Key_S)) && !(pressedKeys.contains(Qt::Key_D)) && !(pressedKeys.contains(Qt::Key_A)) )  //1
            {
                 Player1->setPos(x,y);
            }


        }

        if(event->type()==QEvent::KeyRelease)
        {

            pressedKeys -= ((QKeyEvent*)event)->key();
        }


        return false;
}

void Reckless_chasing::on_Quit_Button_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Quit","Do you want to quit ?");
    if( reply == QMessageBox::Yes)
    {
        parentWidget()->show();
        this->close();
        qDebug() <<"play\n";
    }
}
