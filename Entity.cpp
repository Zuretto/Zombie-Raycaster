#include "Entity.hpp"
#include <iostream>
Entity::Entity(){}
Entity::~Entity(){
    std::cout << "ended life of Entity" << std::endl;
}
int Entity::getType(){
    return ENTITY;
}
double Entity::getPosX() const {
    return posX;
}
double Entity::getPosY() const {
    return posY;
}
double Entity::getRadius(){
    return radius;
}
void Entity::onApproach(Player *player){}
bool Entity::canBeDeleted(){
    return couldDelete;
}
Barrel::Barrel(double xPos, double yPos){
    posX = xPos;
    posY = yPos;
    radius = 0.5;
    xVelocity = 0;
    yVelocity = 0;
    couldDelete = 0;
}
Barrel::~Barrel(){
}
int Barrel::getType(){
    return BARREL;
}

void Barrel::onApproach(Player *player){
    double distance = sqrt(pow(this->getPosX() - player->getPosX(), 2) + pow(this->getPosY() - player->getPosY(), 2));
    if(distance < player->getRadius() + this->getRadius()){
        xVelocity = player->getMoveSpeed() * player->getdirX();
        yVelocity = player->getMoveSpeed() * player->getdirY();
    }
}

void Barrel::onUpdate(sf::Time deltaT, Map *map){
    auto map_vect = map->getMapVector();
    
    double xRadius = -radius * ((xVelocity < 0) - (0 < xVelocity));
    double yRadius = -radius * ((yVelocity < 0) - (0 < yVelocity));
    double futureX = posX + xRadius + xVelocity * deltaT.asSeconds();
    double futureY = posY + yRadius + yVelocity * deltaT.asSeconds();

    if(map_vect[int(futureX)][int(posY + yRadius)] > 0) xVelocity = -xVelocity;
    if(map_vect[int(posX + xRadius)][int(futureY)] > 0) yVelocity = -yVelocity;
    this->posX += xVelocity * deltaT.asSeconds();
    this->posY += yVelocity * deltaT.asSeconds();
    if(xVelocity > 0){
       xVelocity -= movementDelay * deltaT.asSeconds();
    } else if (xVelocity < 0) xVelocity += movementDelay * deltaT.asSeconds();
    if(yVelocity > 0){
       yVelocity -= movementDelay * deltaT.asSeconds();
    } else if (yVelocity < 0) yVelocity += movementDelay * deltaT.asSeconds();
}

Pillar::Pillar(double xPos, double yPos){
    posX = xPos;
    posY = yPos;
    radius = 0.5;
    couldDelete = 0;
}
Pillar::~Pillar(){
}
int Pillar::getType(){
    return PILLAR;
}
void Pillar::onApproach(Player *player){}

Ammo_Shotgun::Ammo_Shotgun(double xPos, double yPos){
    posX = xPos;
    posY = yPos;
    radius = 0.5;
    couldDelete = 0;
}
Ammo_Shotgun::~Ammo_Shotgun(){}
int Ammo_Shotgun::getType(){
    return AMMO_SHOTGUN;
}
void Ammo_Shotgun::onApproach(Player *player){
    double distance = sqrt(pow(this->getPosX() - player->getPosX(), 2) + pow(this->getPosY() - player->getPosY(), 2));
    if(distance < player->getRadius() + this->getRadius()){
        player->increaseAmmo(SHOTGUN, ammoStackAmount);
        this->couldDelete = 1;
    }
}

Ammo_Pistol::Ammo_Pistol(double xPos, double yPos){
    posX = xPos;
    posY = yPos;
    radius = 0.5;
    couldDelete = 0;
}
Ammo_Pistol::~Ammo_Pistol(){}
int Ammo_Pistol::getType(){
    return AMMO_PISTOL;
}
void Ammo_Pistol::onApproach(Player *player){
    double distance = sqrt(pow(this->getPosX() - player->getPosX(), 2) + pow(this->getPosY() - player->getPosY(), 2));
    if(distance < player->getRadius() + this->getRadius()){
        player->increaseAmmo(PISTOL, ammoStackAmount);
        this->couldDelete = 1;
    }
}
