#ifndef RECKLESS_CHASING_H
#define RECKLESS_CHASING_H

#include "player.h"
#include <QDialog>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QVector>

namespace Ui {
class Reckless_chasing;
}

class Reckless_chasing : public QDialog
{
    Q_OBJECT

public:
    QPointF window_size;

    QSet<int> pressedKeys;
    player *Player = new player();
    QVector<player *> Other_player;

    QPointF mouse_pos;

    explicit Reckless_chasing(QWidget *parent = nullptr);
    ~Reckless_chasing();
    bool eventFilter(QObject * obj, QEvent * event);
    QPointF get_MousePos();
    void fixed_Pos(QPointF center,bool isUp);
    void initialize_pos();
    bool is_boundary_crossed(double x, double y, double initialx, double initialy);

private slots:

private:
    Ui::Reckless_chasing *ui;
};

#endif // RECKLESS_CHASING_H

