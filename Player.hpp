#pragma once
#include "definitions.hpp"
#include "Weapon.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <memory>
#include "Map.hpp"
#include "Enemy.hpp"
#include "Entity.hpp"
class Entity;
class Weapon;
class Enemy;
class Player{
private:
    std::shared_ptr<Weapon> weapons[WEAPON_TYPES_NUMBER];
    static constexpr double maxHealthPoints = 100;
    int    drawnWeapon;
    double healthPoints;
    double radius;
    double moveSpeed;
    double rotationSpeed;
    double posX;
    double posY; //x and y start position
    double dirX;
    double dirY; //direction vector
    double planeX;
    double planeY; //FOV
    
public:
    Player(double xpos, double ypos, double xdir, double ydir, double viewAngle);
    double getPosX();   
    double getPosY();
    double getdirX();
    double getdirY();
    double getplaneX();
    double getplaneY();
    double getRadius();
    double getMoveSpeed();
    int    getDrawnWeapon();
    int    getWeaponState();
    int    getDrawnWeaponAmmo();
    void   increaseAmmo(int weapon_type, int amount);
    double getCurrentHp();
    double getMaxHp();
    void   increaseHp(double heal);
    void   decreaseHp(double damage);
    void   forward(sf::Time deltaT, Map *worldMap, std::vector <std::shared_ptr<Entity>> entities);
    void   backward(sf::Time deltaT,Map *worldMap, std::vector <std::shared_ptr<Entity>> entities);
    void   rotateRight(sf::Time deltaT, Map *worldMap);
    void   rotateLeft(sf::Time deltaT, Map *worldMap);
    void   performShoot(Map *worldMap, std::vector <std::shared_ptr<Enemy>> &enemies);
    void   handleWeaponSwap(int weaponToChange);
    ~Player();
};