#pragma once
#include <iostream>
#include <vector>
#include "definitions.hpp"
#include "Player.hpp"

class Weapon;
class Player;
class Enemy{
protected:
    int    healthPoints;
    double moveSpeed;
    double posX;
    double posY;
    double radius;
    sf::Clock deadClock;
public:
    Enemy();
    virtual ~Enemy();
    virtual int getType();
    double getPosX() const;
    double getPosY() const;
    double getRadius();
    int getHp();
    int calculateState();
    void lowerHp(unsigned int damage);
    void moveTowardsPlayer(sf::Time deltaT, Player *player);
};

class Zombie : public Enemy{
public:
    Zombie(double posX, double posY);
    ~Zombie();
    int getType() override;
};

class Skeleton: public Enemy{
public:
    Skeleton(double posX, double posY);
    ~Skeleton();
    int getType() override;
};