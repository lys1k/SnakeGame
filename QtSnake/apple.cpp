#include "apple.h"
#include "controller.h"


void Apple::setPoint(QPoint point){
    this->apple_point = point;
}


QPoint Apple::getPoint(){
    return this->apple_point;
}


void Apple::placeApple(){
    srand(time(0) + 1);
    QPoint point;
    point.setX(rand() % WIDTH);
    point.setY(rand() % HEIGHT);
    this->setPoint(point);

}


int Apple::checkApple(QList <QPoint> snake){
    if(snake.contains(this->getPoint())){
        placeApple();
        return 1;
    }
    else{
       return 0;
    }
}
