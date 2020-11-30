#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <iostream>
#include <thread>
#include <algorithm>
#include <unistd.h>
#include "definitions.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Entity.hpp"
#include "Weapon.hpp"
#include "Enemy.hpp"
class Game{
private:

    struct {
        Player *structPlayer;
        bool operator()(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) const{   
            return pow(a->getPosX() - structPlayer->getPosX(), 2) + pow(a->getPosY() - structPlayer->getPosY(), 2) 
                >=  pow(b->getPosX() - structPlayer->getPosX(), 2) + pow(b->getPosY() - structPlayer->getPosY(), 2);
        }   
        bool operator()(std::shared_ptr<Enemy> a, std::shared_ptr<Enemy> b) const{   
            return pow(a->getPosX() - structPlayer->getPosX(), 2) + pow(a->getPosY() - structPlayer->getPosY(), 2) 
                >=  pow(b->getPosX() - structPlayer->getPosX(), 2) + pow(b->getPosY() - structPlayer->getPosY(), 2);
        }
    }spriteComp;

    Player *player;
    Map *worldMap;
    std::vector <std::shared_ptr<Entity>> entities;
    std::vector <std::shared_ptr<Enemy>> enemies;
    sf::Texture wallTexturesPx[8][texWidth]; //table consisting of 1-pixel wide textures
    sf::Texture entityTexturesPx[ENTITY_TYPES_NUMBER][entityWidth];
    sf::Texture enemyTexturesPx[ENEMY_TYPES_NUMBER][enemyWidth];
    sf::Texture weaponTextures[GUN_TYPES_NUMBER][weapon_states];

    int weaponState;
    sf::Clock weaponClock;
    double ZBuffer[casterWidth]; //buffer used to draw sprites, contains perpWallDists for each x
public:
    Game(Player* player);
    void drawScene(sf::RenderTarget & target);
    void drawWeapon(sf::RenderTarget &target);
    void drawEntity(sf::RenderTarget &target, std::shared_ptr<Entity> &entity);
    void drawEnemy(sf::RenderTarget &target, std::shared_ptr<Enemy> &enemy);
    void drawSprites(sf::RenderTarget &target);
    void setWeaponState(int state);
    void onUpdate(sf::Time deltaT);
    int getWeaponState();



    
};
