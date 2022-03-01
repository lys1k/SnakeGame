#ifndef SNAKE_H
#define SNAKE_H
#include "controller.h"

class Snake{
private:
      QList<QPoint> body;
      QPoint head = body[0];

public:
      QPoint getHead();

};

#endif // SNAKE_H
