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
    sf::Clock weaponClock;

public:
    Weapon();
    virtual ~Weapon();
    virtual int getType();
    int getDamage();
    int getRange();
    int getAmmo();
    int calculateState();
    virtual void increaseAmmo(int amount);
    virtual void performShoot(Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> &enemies);
};

class Pistol : public Weapon{
public:
    Pistol();
    ~Pistol();
    int getType() override;
};

class Shotgun : public Weapon{
private:
    static constexpr double shotAngle = M_PI / 18 / 2; //angle of shot, M_PI/18 / 2 is 5 degrees.
    static constexpr int    pelletNumber = 10;     //amount of pellets in one shot
public:
    Shotgun();
    ~Shotgun();
    int getType() override;
    void performShoot(Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> &enemies) override; //override so that it shots in a cone.
};

class Fist : public Weapon{
public:
    Fist();
    ~Fist();
    int getType() override;
    void performShoot(Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> &enemies) override; //overrided because Fist doesn't need ammo
};



