#include "Enemy.hpp"
Enemy::Enemy(){}
Enemy::~Enemy(){
    std::cout << "ended life of Enemy" << std::endl;
}
int Enemy::getType(){
    return ENEMY;
}
double Enemy::getPosX() const {
    return posX;
}
double Enemy::getPosY() const {
    return posY;
}
double Enemy::getRadius(){
    return radius;
}
void Enemy::moveTowardsPlayer(sf::Time deltaT, Player *player){
    double speed = this->moveSpeed * deltaT.asSeconds();
    double deltaX = -this->posX + player->getPosX();
    double deltaY = -this->posY + player->getPosY();
    double dist = sqrt(pow(deltaX, 2)+ pow(deltaY,2));
    if(dist > 0.5){
        double dirX = deltaX / dist;
        double dirY = deltaY / dist;
        this->posX += dirX * speed;
        this->posY += dirY * speed;
    }
}


Zombie::Zombie(double posX, double posY){
    this->moveSpeed = 4;
    this->healthPoints = 150;
    this->posX = posX;
    this->posY = posY;
    this->radius = 0.9;
}
Zombie::~Zombie(){
}
int Zombie::getType(){
    return ZOMBIE;
}

Skeleton::Skeleton(double posX, double posY){
    this->moveSpeed = 8;
    this->healthPoints = 75;
    this->posX = posX;
    this->posY = posY;
    this->radius = 0.4;
}
Skeleton::~Skeleton(){

}
int Skeleton::getType(){
    return SKELETON;
}