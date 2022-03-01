#include "bonus.h"
#include "controller.h"


void Bonus::setPoint(QPoint point){
    this->bonus_point = point;
}


QPoint Bonus::getPoint(){
    return this->bonus_point;
}


int Bonus::getEnergy(){
    return this->energy;
}


void Bonus::setEnergy(int score){
    this->energy = score;
}


int Bonus::checkBonus(QList<QPoint> snake){
    int score = 0;
    if(snake.contains(this->bonus_point)){
        score = this->energy;
        this->placeBonus();
    }
    return score;
}


void Bonus::placeBonus(){
    srand(time(0));
    QPoint point;
    point.setX(rand() % WIDTH);
    point.setY(rand() % HEIGHT);
    this->setPoint(point);
    int r = 1 + rand() % 5;
    this->setEnergy(r);
}

