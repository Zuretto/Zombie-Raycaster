#pragma once
#include "definitions.hpp"
#include "Weapon.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <memory>
#include "Map.hpp"
#include "Enemy.hpp"
class Weapon;
class Enemy;
class Player{
private:
    //Map *worldMap;
    std::shared_ptr<Weapon> weapons[GUN_TYPES_NUMBER];
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
    Player(double xpos, double ypos, double xdir, double ydir, double viewAngle);
    double getPosX();   
    double getPosY();
    double getdirX();
    double getdirY();
    double getplaneX();
    double getplaneY();
    double getRadius();
    int    getDrawnWeapon();
    void   forward(sf::Time deltaT, Map *worldMap);
    void   backward(sf::Time deltaT,Map *worldMap);
    void   rotateRight(sf::Time deltaT, Map *worldMap);
    void   rotateLeft(sf::Time deltaT, Map *worldMap);
    void   performShoot(Map *worldMap, std::vector <std::shared_ptr<Enemy>> &enemies);
    ~Player();
};