#pragma once
#include "definitions.hpp"
#include "SFML/Graphics.hpp"
class Entity{
protected:
    double posX;
    double posY;
    double radius;
public:
    Entity();
    virtual ~Entity();
};

class Barrel : public Entity{
//private:
public:
    Barrel(double posX, double posY);
    ~Barrel();
    double getPosX();
    double getPosY();
    double getRadius();
};
