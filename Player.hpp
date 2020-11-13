#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.hpp"
class Player : public sf::Drawable{
private:
    double radius;
    sf::CircleShape *shape;
    double moveSpeed;
    double posX;
    double posY; //x and y start position
    double dirX;
    double dirY; //direction vector
    double planeX;
    double planeY; //FOV
    Map *map;
public:
    Player(double xpos, double ypos, double xdir, double ydir, double xplane, double yplane, Map *mapp);
    double getPosX();
    double getposY();
    double getdirX();
    double getdirY();
    double getplaneX();
    double getplaneY();
    void forward(sf::Time deltaT);
    void backward(sf::Time deltaT);
    ~Player();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        //target.draw(shape);
        // ... or use the low-level API
        // ... or draw with OpenGL directly
//private:
//    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};