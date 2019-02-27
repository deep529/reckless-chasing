#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_host_button_clicked() {
    this->screen = new ServerScreen(4567, 4, this);
    static_cast<ServerScreen*>(this->screen)->show();
    this->hide();
}

void MainWindow::on_join_button_clicked() {
    this->screen = new ClientScreen(4567, this);
    static_cast<ClientScreen*>(this->screen)->show();
    this->hide();
}
