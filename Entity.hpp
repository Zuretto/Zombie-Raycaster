#pragma once
#include "SFML/Graphics.hpp"
#include "definitions.hpp"


class Entity{
protected:
    double posX;
    double posY;
    double radius;
public:
    Entity();
    virtual ~Entity();
    virtual int getType();
    double getPosX() const;
    double getPosY() const;
    double getRadius();
};

class Barrel : public Entity{
public:
    Barrel(double posX, double posY);
    ~Barrel();
    int getType() override;
};

class Pillar : public Entity{
public:
    Pillar(double posX, double posY);
    ~Pillar();
    int getType() override;
};
