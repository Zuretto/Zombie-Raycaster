#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "definitions.hpp"
#include "Player.hpp"
#include "Entity.hpp"

class Entity;
class Weapon;
class Player;
class Enemy{
protected:
    bool   activated;
    int    healthPoints;
    int    damage;
    double moveSpeed;
    double posX;
    double posY;
    double radius;
    sf::Clock deadClock;
    sf::Clock attackClock;
    double attackCooldown;

    bool isPlayerBehindTheWall(Player *player, Map *worldmap);
    bool futurePoseXEnemyIntersection(std::vector <std::shared_ptr<Enemy>> enemies, double futureX);
    bool futurePoseYEnemyIntersection(std::vector <std::shared_ptr<Enemy>> enemies, double futureY);
    virtual void handleMoveLogic(sf::Time deltaT, Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> enemiesWithoutThis);
    virtual void handleAttackLogic(Player *player, std::vector <std::shared_ptr<Entity>> &entities);

public:
    Enemy();
    virtual ~Enemy();
    virtual int getType();
    double getPosX() const;
    double getPosY() const;
    double getRadius();
    int getHp();
    bool isActive();

    int calculateState();
    void lowerHp(unsigned int damage);
    void handleLogic(sf::Time deltaT, Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> enemiesWithoutThis, std::vector <std::shared_ptr<Entity>> &entities);
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

class FireWizard : public Enemy{
public:
    FireWizard(double posX, double posY);
    ~FireWizard();
    int getType() override;
    void handleMoveLogic(sf::Time deltaT, Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> enemies){}
    void handleAttackLogic(Player *player, std::vector <std::shared_ptr<Entity>> &entities);
};