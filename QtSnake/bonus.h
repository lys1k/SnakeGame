#ifndef BONUS_H
#define BONUS_H

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>


class Bonus{
private:
    QPoint bonus_point;
    int energy;

public:
    void setPoint(QPoint point);
    QPoint getPoint();

    void setEnergy(int score);
    int getEnergy();

    void placeBonus();
    int checkBonus(QList<QPoint> snake);
};



#endif // BONUS_H
