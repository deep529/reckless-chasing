#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reckless_chasing.h"
#include "serverwindow.h"

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
    void on_Play_Button_clicked();
    void on_Developer_Button_clicked();
    void on_Quit_Button_clicked();
    void on_actionPlay_triggered();
    void on_actionDeveloper_triggered();
    void on_actionQuit_triggered();
    void on_actionAbout_Game_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionHelp_triggered();
    void on_Host_Button_clicked();
    void on_Join_Button_clicked();
    void on_plus_button_clicked();
    void on_minus_button_clicked();

private:
    Ui::MainWindow *ui;
    ServerWindow *serwin;
    // ClientWindow *clwin;

    void hide_host_options();
    void show_host_options();
    void hide_join_options();
    void show_join_options();
    void show_error();
};

#endif // MAINWINDOW_H
