#ifndef APPLE_H
#define APPLE_H

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>

class Apple{
private:
    QPoint apple_point;

public:
    void setPoint(QPoint point);
    QPoint getPoint();

    void placeApple();
    int checkApple(QList <QPoint> snake);
};

#endif // APPLE_H
