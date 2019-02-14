#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reckless_chasing.h"

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

private:
    Ui::MainWindow *ui;
    Reckless_chasing *play;
};

#endif // MAINWINDOW_H
