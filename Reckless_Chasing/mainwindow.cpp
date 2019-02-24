#include <QMessageBox>
#include <QPixmap>
#include <QToolTip>
#include <QToolBar>
#include <QRadioButton>
#include <QVector>
#include <QString>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setFixedSize(900,600);

    this->hide_host_options();
    this->hide_join_options();

    ui->player_count->display(0);
    ui->Name_lineEdit->setText("Player 1");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::hide_host_options() {
    ui->plus_button->setHidden(true);
    ui->minus_button->setHidden(true);
    ui->player_count->setHidden(true);
    ui->player_count_label->setHidden(true);
}

void MainWindow::show_host_options() {
    ui->plus_button->setHidden(false);
    ui->minus_button->setHidden(false);
    ui->player_count->setHidden(false);
    ui->player_count_label->setHidden(false);
}

void MainWindow::hide_join_options() {
    ui->IP_Address_lineEdit->setHidden(true);
    ui->IP_Address_label->setHidden(true);
}

void MainWindow::show_join_options() {
    ui->IP_Address_lineEdit->setHidden(false);
    ui->IP_Address_label->setHidden(false);
}

void MainWindow::on_Host_Button_clicked() {
    this->hide_join_options();
    ui->IP_Address_lineEdit->setText("");

    if(ui->player_count->intValue() < 2) {
        ui->player_count->display(2);
    }

    this->show_host_options();
}

void MainWindow::on_Join_Button_clicked() {
    this->hide_host_options();
    ui->player_count->display(0);

    ui->IP_Address_lineEdit->setText("127.0.0.1");
    this->show_join_options();
}

void MainWindow::on_plus_button_clicked() {
    int players = ui->player_count->intValue();

    if(players < 4) {
        ui->player_count->display(players+1);
    }
}

void MainWindow::on_minus_button_clicked() {
    int players = ui->player_count->intValue();

    if(players > 2) {
        ui->player_count->display(players-1);
    }
}

void MainWindow::on_Play_Button_clicked() {
    if (ui->Name_lineEdit->text().isEmpty()) {
        this->show_error();
        return;
    }
    if (!ui->Join_Button->isChecked() && !ui->Host_Button->isChecked()) {
        this->show_error();
        return;
    }
    if (ui->Join_Button->isChecked() && ui->IP_Address_lineEdit->text().isEmpty()) {
        this->show_error();
        return;
    }
    if (ui->Host_Button->isChecked() && (ui->player_count->intValue() < 2 || ui->player_count->intValue() > 4)) {
        this->show_error();
        return;
    }


    if (ui->Host_Button->isChecked()) {
        qDebug() << "Host detected";
        this->serwin = new ServerWindow(this);
        this->hide();
        this->serwin->setWindowTitle("Reckless Chasing(Play)");
        this->serwin->show();
    }
    else if (ui->Join_Button->isChecked()) {
        /*play = new Reckless_chasing(this);
        this->hide();
        play->setWindowTitle("Reckless Chasing(Play)");
        play->show();*/
    }
}

void MainWindow::show_error() {
    QVector<QString> Unfilled;

    if((!(ui->Join_Button->isChecked())) && (!(ui->Host_Button->isChecked()))) {
        Unfilled.push_back("Host or Join");
    }
    if(ui->Name_lineEdit->text().isEmpty()) {
        Unfilled.push_back("Name");
    }
    if((ui->IP_Address_lineEdit->text().isEmpty()) && (ui->Join_Button->isChecked())) {
        Unfilled.push_back("IP Address");
    }

    QString temp = "Please fill up these information to continue :";

    for(int i = 0; i < Unfilled.size(); i++) {
        temp = temp + "\n" + char(i+49) + ".\t" +Unfilled[i];
    }

    QMessageBox::critical(this,"Error",temp);
    return;
}

void MainWindow::on_Developer_Button_clicked()
{
    QMessageBox::information(this,"Developer's","TEAM NO. : 14\n1.Deep Diwani\n2.Dheeraj Agarwalla\n3.Gajanan Shetkar\n4.Anurag Patil");
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

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this,"About Qt");
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

void MainWindow::on_actionAbout_Game_triggered()
{

}

void MainWindow::on_actionHelp_triggered()
{

}
