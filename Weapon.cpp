#include "Weapon.hpp"
Weapon::Weapon(){}
Weapon::~Weapon(){}
int Weapon::getType(){
    return WEAPON;
}
int Weapon::getDamage(){
    return damage;
}
int Weapon::getRange(){
    return range;
}
Pistol::Pistol(){
    damage = 40;
    range = 20;
    shotCooldown = 0.25;
}
Pistol::~Pistol(){};
int Pistol::getType(){
    return PISTOL;
}
