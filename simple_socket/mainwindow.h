#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "serverscreen.h"
#include "clientscreen.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_host_button_clicked();
    void on_join_button_clicked();

private:
    Ui::MainWindow *ui;
    QObject *screen;
};

#endif // MAINWINDOW_H
