#pragma once
#include "definitions.hpp"
#include "SFML/Graphics.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include <memory>

class Player;
class Enemy;
class Weapon{
protected:
    int damage;
    int range;
    int ammo;
    double shotCooldown;
    sf::Clock gunClock;

public:
    Weapon();
    virtual ~Weapon();
    virtual int getType();
    int getDamage();
    int getRange();
    virtual void performShoot(Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> &enemies);
};

class Pistol : public Weapon{
public:
    Pistol();
    ~Pistol();
    int getType() override;
};



