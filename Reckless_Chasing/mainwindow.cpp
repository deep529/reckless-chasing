#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QToolTip>
#include <QRadioButton>
#include <QToolBar>
#include <QVector>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->toolBar->setFixedHeight(30);

    QPixmap background(":/images/Images/Home_Background.jpg");              //For backgroung image of the main window.
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #000000; border: 1px solid white; }"              //For customizing different button.
                        "QRadioButton::indicator:checked {background-color:#000000; border: 2px solid white;}"
                        "QRadioButton::indicator:unchecked {background-color:#ffffff; border: 2px solid white;}");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Developer_Button_clicked()
{
    QMessageBox::information(this,"Developer's","TEAM NO. : 14\n1.Deep Diwani\n2.Dheeraj Agarwalla\n3.Gajanan Shetkar\n4.Anurag Patil");
}

void MainWindow::on_Quit_Button_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Quit","Do you want to quit ?");
    if( reply == QMessageBox::Yes)
    {
        QApplication::quit();
        qDebug() <<"home";
    }
}

void MainWindow::on_Play_Button_clicked()
{
    if(((ui->Total_1_Player->isChecked())||(ui->Total_2_Player->isChecked())||(ui->Total_3_Player->isChecked())||(ui->Total_4_Player->isChecked()))&&(!(ui->Name_lineEdit->text().isEmpty()))&&(!(ui->IP_Address_lineEdit->text().isEmpty())))
    {
        play = new Reckless_chasing(this);
        this->hide();                                        //For Hiding the home window when play window is going to open.
        play->setWindowTitle("Reckless Chasing(Play)");
        play->show();
    }
    else
    {
        QVector<QString> Unfilled;
        if(!((ui->Total_1_Player->isChecked())||(ui->Total_2_Player->isChecked())||(ui->Total_3_Player->isChecked())||(ui->Total_4_Player->isChecked())))
        {
            Unfilled.push_back("No. of Player");
        }
        if(ui->Name_lineEdit->text().isEmpty())
        {
            Unfilled.push_back("Name");
        }
        if(ui->IP_Address_lineEdit->text().isEmpty())
        {
            Unfilled.push_back("IP Address");
        }
        QString temp = "Please fill up these information to continue :";
        for(int i = 0; i < Unfilled.size(); i++)
        {
            temp = temp + "\n" + char(i+49) + ".\t" +Unfilled[i];
        }
        QMessageBox::critical(this,"Error",temp);
        return;
    }
}

void MainWindow::on_actionPlay_triggered()
{
    on_Play_Button_clicked();
}

void MainWindow::on_actionDeveloper_triggered()
{
    on_Developer_Button_clicked();
}

void MainWindow::on_actionQuit_triggered()
{
    on_Quit_Button_clicked();
}

void MainWindow::on_actionAbout_Game_triggered()
{

}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this,"About Qt");
}

void MainWindow::on_actionHelp_triggered()
{

}
