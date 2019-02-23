#ifndef RECKLESS_CHASING_H
#define RECKLESS_CHASING_H

#include <QDialog>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

namespace Ui {
class Reckless_chasing;
}

class Reckless_chasing : public QDialog
{
    Q_OBJECT

public:
    QSet<int> pressedKeys;

    explicit Reckless_chasing(QWidget *parent = nullptr);
    ~Reckless_chasing();
    bool eventFilter(QObject * obj, QEvent * event);

private slots:
    void on_Quit_Button_clicked();

private:
    Ui::Reckless_chasing *ui;
};

#endif // RECKLESS_CHASING_H
