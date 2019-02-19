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
#include <QRect>
#include <QDebug>

Reckless_chasing::Reckless_chasing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reckless_chasing)
{
    ui->setupUi(this);

   QPixmap background(":/images/Images/Play_Background.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(70);
    QGraphicsScene *scene = new QGraphicsScene();
    player *Player1 = new player();
    Player1->setRect(0,0,100,100);
    scene->addItem(Player1);
    Player1->setFlag(QGraphicsItem::ItemIsFocusable);
    Player1->setFocus();
    QGraphicsView *view = new QGraphicsView(scene);
    view->setWindowTitle("Reckless Chasing(Play)");
    layout->addWidget(view);
    view->show();
}

Reckless_chasing::~Reckless_chasing()
{
    delete ui;
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
