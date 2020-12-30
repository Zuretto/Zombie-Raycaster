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

Barrel::Barrel(double xPos, double yPos){
    posX = xPos;
    posY = yPos;
    radius = 0.5;
}
Barrel::~Barrel(){
}
int Barrel::getType(){
    return BARREL;
}
Pillar::Pillar(double xPos, double yPos){
    posX = xPos;
    posY = yPos;
    radius = 0.5;
}
Pillar::~Pillar(){
}
int Pillar::getType(){
    return PILLAR;
}