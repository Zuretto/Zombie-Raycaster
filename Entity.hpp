#pragma once
#include "SFML/Graphics.hpp"
#include "definitions.hpp"
#include "Player.hpp"

class Player;
class Entity{
protected:
    double posX;
    double posY;
    double radius;
    bool   couldDelete; // 0 if Game shouldn't delete the entity, 1 if should
public:
    Entity();
    virtual ~Entity();
    virtual int getType();
    double getPosX() const;
    double getPosY() const;
    bool   canBeDeleted();
    double getRadius();
    virtual void onApproach(Player *player);                           //checks if Player is close enough and then does sth with that information
    virtual void onUpdate(sf::Time deltaT, Map *map){}                 //performs onUpdate actions like moving in some direction (or nothing)
};

class Barrel : public Entity{
protected:
    static constexpr double movementDelay = 4; //meters per square seconds
    double xVelocity;
    double yVelocity;
public:
    Barrel(double posX, double posY);
    ~Barrel();
    int getType() override;
    void onApproach(Player *player) override;
    void onUpdate(sf::Time deltaT, Map *map) override;
};

class Pillar : public Entity{
public:
    Pillar(double posX, double posY);
    ~Pillar();
    int getType() override;
    void onApproach(Player *player) override;
};

class Ammo_Shotgun : public Entity{
private:
    static constexpr int ammoStackAmount = 8;
public:
    Ammo_Shotgun(double posX, double posY);
    ~Ammo_Shotgun();
    int getType() override;
    void onApproach(Player *player) override;
};

class Ammo_Pistol : public Entity{
private:
    static constexpr int ammoStackAmount = 12;
public:
    Ammo_Pistol(double posX, double posY);
    ~Ammo_Pistol();
    int getType() override;
    void onApproach(Player *player) override;
};

class Hamburger : public Entity{
private:
    static constexpr int healthRegen = 25;
public:
    Hamburger(double posX, double posY);
    ~Hamburger();
    int getType() override;
    void onApproach(Player *player) override;
};

class Soda : public Entity{
private:
    static constexpr int healthRegen = 10;
public:
    Soda(double posX, double posY);
    ~Soda();
    int getType() override;
    void onApproach(Player *player) override;
};

class Fireball : public Entity{
private:
    static constexpr double moveSpeed = 2;
    static constexpr double damage =   20;
    double xVelocity;
    double yVelocity;
public:
    Fireball(double posX, double posY, double dirX, double dirY);
    ~Fireball();
    int getType() override;
    void onApproach(Player *player) override;
    void onUpdate(sf::Time deltaT, Map *map) override;
};

