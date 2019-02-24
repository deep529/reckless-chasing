#ifndef RECKLESS_CHASING_H
#define RECKLESS_CHASING_H

#include "player.h"
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

    explicit Reckless_chasing(QWidget *parent = nullptr);
    ~Reckless_chasing();

private slots:

private:
    Ui::Reckless_chasing *ui;
};

#endif // RECKLESS_CHASING_H
