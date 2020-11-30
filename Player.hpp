#pragma once
#include "definitions.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Map.hpp"
#include "Weapon.hpp"
class Player{
private:
    //Map *worldMap;
    Weapon *weapons[GUN_TYPES_NUMBER];
    int drawnGun;
    double healthPoints;
    double radius;
    double moveSpeed;
    double rotationSpeed;
    double posX;
    double posY; //x and y start position
    double dirX;
    double dirY; //direction vector
    double planeX;
    double planeY; //FOV
    
public:
    Player(double xpos, double ypos, double xdir, double ydir, double xplane, double yplane);
    double getPosX();
    double getPosY();
    double getdirX();
    double getdirY();
    double getplaneX();
    double getplaneY();
    double getRadius();
    int getDrawnWeapon();
    void forward(sf::Time deltaT, Map *worldMap);
    void backward(sf::Time deltaT,Map *worldMap);
    void rotateRight(sf::Time deltaT, Map *worldMap);
    void rotateLeft(sf::Time deltaT, Map *worldMap);
    ~Player();
};