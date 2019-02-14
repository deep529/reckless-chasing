#ifndef RECKLESS_CHASING_H
#define RECKLESS_CHASING_H

#include <QDialog>

namespace Ui {
class Reckless_chasing;
}

class Reckless_chasing : public QDialog
{
    Q_OBJECT

public:
    explicit Reckless_chasing(QWidget *parent = nullptr);
    ~Reckless_chasing();

private slots:
    void on_Quit_Button_clicked();

private:
    Ui::Reckless_chasing *ui;
};

#endif // RECKLESS_CHASING_H
