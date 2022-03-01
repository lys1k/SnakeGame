#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include "apple.h"
#include "bonus.h"

const int SIZE = 25;
const int MARGIN = 5;
const int HEIGHT = 20;
const int WIDTH = 20;

const int TIME = 300;

enum Direction{
    BACKWARD,
    FORWARD,
    LEFT,
    RIGHT
};

class Controller : public QWidget{
    Q_OBJECT

public:
    Controller(QWidget *parent = 0);
    ~Controller();

    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

    void InitGame();
    void InitWall();
    void LoadImages();
    void PlaceItems();
    void ItemsUpdate();
    void SnakeUpdate();
    void fasten();
    void Pause();
    void End();
    bool IsOver();

private slots:
    void Update();

private:
    Apple apple;
    Bonus bonus;
    QList<QPoint> snake;
    QList<QPoint> wall;    
    Direction last_direction;
    QTimer *gameTimer;
    bool isPause;
    int score;
    int lives_num;
    int level;
    int apples;
    QImage apple_image;
    QImage bonus_image;
    QImage snake_image;
    QImage head_right;
    QImage head_left;
    QImage head_down;
    QImage head_up;
    QImage wall_image;

};

#endif // CONTROLLER_H
