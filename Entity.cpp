#include "Entity.hpp"
Entity::Entity(){}
Entity::~Entity(){}


Barrel::Barrel(double xPos, double yPos){
    posX = xPos;
    posY = yPos;
    radius = 0.5;
}
Barrel::~Barrel(){}
double Barrel::getPosX(){
    return posX;
}
double Barrel::getPosY(){
    return posY;
}
double Barrel::getRadius(){
    return radius;
}