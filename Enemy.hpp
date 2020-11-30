#pragma once
#include <iostream>
#include "definitions.hpp"
#include "Player.hpp"
enum enemy_num {ENEMY, ZOMBIE, SKELETON, ENEMY_TYPES_NUMBER};

class Enemy{
protected:
    int healthPoints;
    double moveSpeed;
    double posX;
    double posY;
    double radius;
public:
    Enemy();
    virtual ~Enemy();
    virtual int getType();
    double getPosX() const;
    double getPosY() const;
    double getRadius();

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