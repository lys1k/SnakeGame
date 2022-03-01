#include <QPainter>
#include <time.h>
#include <QTimer>
#include <QTime>
#include <QString>
#include <QTime>
#include <QMessageBox>
#include "controller.h"
#include "apple.h"
#include "bonus.h"
#include <QDir>


Controller::Controller(QWidget *parent): QWidget(parent){
    resize(MARGIN * 5 + (WIDTH + 8) * SIZE, MARGIN * 10 + HEIGHT * SIZE);
    InitGame();
}


Controller::~Controller(){}


void Controller::InitGame(){
    LoadImages();
    snake.clear();

    for(int j = 3; j >= 0; j--)
        snake.push_back(QPoint(j + 5,10));

    last_direction = BACKWARD;
    lives_num = 3;
    score = 0;
    apples = 0;
    level = 1;
    isPause = false;

    InitWall();
    PlaceItems();

    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(Update()));
    gameTimer->start(TIME);
}


void Controller::PlaceItems(){
    srand(time(0));

    apple.placeApple();
    while(wall.contains(apple.getPoint())){
        apple.placeApple();
    }

    bonus.placeBonus();
    while(wall.contains(bonus.getPoint())){
        bonus.placeBonus();
    }
}


void Controller::InitWall(){
    wall.append(QPoint(3,3));
    wall.append(QPoint(5,5));
    wall.append(QPoint(4,4));

    wall.append(QPoint(14,14));
    wall.append(QPoint(15,15));
    wall.append(QPoint(16,16));

    wall.append(QPoint(3,16));
    wall.append(QPoint(4,15));
    wall.append(QPoint(5,14));

    wall.append(QPoint(14,5));
    wall.append(QPoint(15,4));
    wall.append(QPoint(16,3));
}


void Controller::ItemsUpdate(){
    int ate = apple.checkApple(snake);
    if(ate == 1){
        score += 10;
        apple.placeApple();
        while(wall.contains(apple.getPoint())){
            apple.placeApple();
        }

        apples +=1;
        if(apples %4 == 0 &&apples > 0 && level < 3){
            fasten();
            level+=1;
        }
    }
    else{
        snake.pop_back();
    }

    int scr = bonus.checkBonus(snake);
    score += scr;
    if(score%3 == 0){
        bonus.placeBonus();
        while(wall.contains(bonus.getPoint())){
            bonus.placeBonus();
        }
    }
}


void Controller::SnakeUpdate(){
    switch(last_direction)    {
    case FORWARD:
        snake.push_front(QPoint(snake.front().x(),snake.front().y()-1));
        break;
    case BACKWARD:
        snake.push_front(QPoint(snake.front().x(),snake.front().y()+1));
        break;
    case LEFT:
        snake.push_front(QPoint(snake.front().x()-1,snake.front().y()));
        break;
    case RIGHT:
        snake.push_front(QPoint(snake.front().x()+1,snake.front().y()));
        break;
    default:
        break;
    }
}


void Controller::Update(){
    SnakeUpdate();
    ItemsUpdate();
    if(IsOver())    {
        gameTimer->stop();
        End();
    }
    update();
}


bool Controller::IsOver(){
    bool flag = false;
    int x = snake.front().x();
    int y = snake.front().y();

    if(x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1)
        flag =  true;

    if(wall.contains(snake[0]))
        flag = true;

    for(int i = 3; i < snake.size(); i++)
        if(snake[i] == snake.front())
            flag =  true;

    if(flag ==true && lives_num > 1){
        lives_num -=1;
        snake.clear();
        last_direction = BACKWARD;

        for(int j=10;j>=0;j--)
            snake.push_back(QPoint(j,2));

        score -= 50;
        return false;
    }

    else if(flag == false){
        return false;
    }

    else{
        return true;
    }
}


void Controller::End(){
    QMessageBox msgBox;
    msgBox.setText("Game over.");
    msgBox.setInformativeText("Do you want to play again?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    int res = msgBox.exec();
    switch (res) {
      case QMessageBox::Yes:
          InitGame();
          break;
      case QMessageBox::No:
          exit(0);
          break;
    }
}


void Controller::Pause(){
    if(!isPause)    {
        isPause = true;
        gameTimer->stop();
    }
    else{
        isPause = false ;
        gameTimer->start(TIME);
    }
}


void Controller::fasten(){
    gameTimer = new QTimer(this);
    connect(gameTimer,SIGNAL(timeout()),this,SLOT(Update()));
    gameTimer->start(TIME - 10);
}


void Controller::LoadImages(){
    apple_image.load("C:\\Users\\Dell\\Desktop\\QtSnake-master\\QtSnake\\Resources\\apple.png");
    bonus_image.load("C:\\Users\\Dell\\Desktop\\QtSnake-master\\QtSnake\\Resources\\Bonus2.png");
    snake_image.load(("C:\\Users\\Dell\\Desktop\\QtSnake-master\\QtSnake\\Resources\\Pit.png"));
    wall_image.load("C:\\Users\\Dell\\Desktop\\QtSnake-master\\QtSnake\\Resources\\Wall.jpg");
    head_right.load("C:\\Users\\Dell\\Desktop\\QtSnake-master\\QtSnake\\Resources\\right.png");
    head_left.load("C:\\Users\\Dell\\Desktop\\QtSnake-master\\QtSnake\\Resources\\left.png");
    head_up.load("C:\\Users\\Dell\\Desktop\\QtSnake-master\\QtSnake\\Resources\\up.png");
    head_down.load("C:\\Users\\Dell\\Desktop\\QtSnake-master\\QtSnake\\Resources\\down.png");
}


void Controller::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(Qt::lightGray);
    painter.setPen(Qt::black);
    painter.drawRect(MARGIN*5, MARGIN*5, WIDTH*SIZE, HEIGHT*SIZE);

    for(int i = 0; i < WIDTH + 2; i++){
        painter.drawImage(i*25, 0,wall_image);
    }
    for(int i = 0; i < WIDTH + 2; i++){
        painter.drawImage(i*25, HEIGHT*SIZE + 25,wall_image);
    }

    for(int i = 1; i < HEIGHT +1 ; i++){
        painter.drawImage(0, i*SIZE,wall_image);
    }
    for(int i = 1; i < HEIGHT + 1; i++){
        painter.drawImage(WIDTH *SIZE + SIZE, i*SIZE,wall_image);
    }

    for(int i = 0; i < wall.length(); i++){
        painter.drawImage(MARGIN*5 + wall[i].x()*SIZE, MARGIN*5+wall[i].y()*SIZE, wall_image);
    }

    for(int i = 1; i < snake.size(); i++)
        painter.drawImage(MARGIN*5+snake[i].x()*SIZE,MARGIN*5+snake[i].y()*SIZE, snake_image);

    if(last_direction == BACKWARD)
        painter.drawImage(MARGIN*5+snake[0].x()*SIZE,MARGIN*5+snake[0].y()*SIZE, head_down);
    else if(last_direction == FORWARD)
       painter.drawImage(MARGIN*5+snake[0].x()*SIZE,MARGIN*5+snake[0].y()*SIZE, head_up);
    else if(last_direction == RIGHT)
         painter.drawImage(MARGIN*5+snake[0].x()*SIZE,MARGIN*5+snake[0].y()*SIZE, head_right);
    else
         painter.drawImage(MARGIN*5+snake[0].x()*SIZE,MARGIN*5+snake[0].y()*SIZE, head_left);

    painter.drawImage(MARGIN*5+apple.getPoint().x()*SIZE,MARGIN*5+apple.getPoint().y()*SIZE, apple_image);
    painter.drawImage(MARGIN*5+bonus.getPoint().x()*SIZE,MARGIN*5+bonus.getPoint().y()*SIZE, bonus_image);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",13));
    painter.drawText(MARGIN*15+WIDTH*SIZE,MARGIN*5+2*SIZE,"score: "+QString::number(score));
    painter.drawText(MARGIN*15+WIDTH*SIZE,MARGIN*5+2*SIZE+50,"lives: "+QString::number(lives_num));
    painter.drawText(MARGIN*15+WIDTH*SIZE,MARGIN*5+2*SIZE+100,"level: "+QString::number(level));
}


void Controller::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Left:
             if(last_direction != RIGHT)
                 last_direction = LEFT;
             break;
        case Qt::Key_Right:
            if(last_direction != LEFT)
                last_direction = RIGHT;
            break;
        case Qt::Key_Up:
            if(last_direction != BACKWARD)
                last_direction = FORWARD;
            break;
        case Qt::Key_Down:
            if(last_direction != FORWARD)
                last_direction = BACKWARD;
            break;
        case Qt::Key_P:
            Pause();
            break;
        default:
            break;
        }
}
