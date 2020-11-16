#pragma once
#include "definitions.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Map.hpp"
class Player{
private:
    Map *worldMap;
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
    Player(double xpos, double ypos, double xdir, double ydir, double xplane, double yplane, Map *mapp);
    double getPosX();
    double getPosY();
    double getdirX();
    double getdirY();
    double getplaneX();
    double getplaneY();
    double getRadius();
    void forward(sf::Time deltaT);
    void backward(sf::Time deltaT);
    void rotateRight(sf::Time deltaT);
    void rotateLeft(sf::Time deltaT);
    ~Player();
};