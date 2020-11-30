#pragma once
#include "definitions.hpp"
#include "SFML/Graphics.hpp"
enum gun_enum {WEAPON, FIST, PISTOL, SHOTGUN, GUN_TYPES_NUMBER};
class Weapon{
protected:
    int damage;
    int range;
    int ammo;
    double shotCooldown;
public:
    Weapon();
    virtual ~Weapon();
    virtual int getType();
    int getDamage();
    int getRange();
};

class Pistol : public Weapon{
public:
    Pistol();
    ~Pistol();
    int getType() override;
};

