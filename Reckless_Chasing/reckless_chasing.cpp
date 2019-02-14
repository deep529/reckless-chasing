#include "reckless_chasing.h"
#include "ui_reckless_chasing.h"
#include <QMessageBox>
#include <QPixmap>

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
    }
}
