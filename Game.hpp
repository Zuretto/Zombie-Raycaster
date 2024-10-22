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
#include "Resource_Manager.hpp"


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
    Resource_Manager *resManager;
    std::vector <std::shared_ptr<Entity>> entities;
    std::vector <std::shared_ptr<Enemy>> enemies;

    void loadObjectsFromFile(std::string fileName);
    double ZBuffer[casterWidth]; //buffer used to draw sprites, contains perpWallDists for each x
    bool checkIfAllEnemiesAreDead();
    void drawScene(sf::RenderTarget & target);
    void drawEntity(sf::RenderTarget &target, std::shared_ptr<Entity> &entity);
    void drawEnemy(sf::RenderTarget &target, std::shared_ptr<Enemy> &enemy);
    void drawSprites(sf::RenderTarget &target);
    void drawWeapon(sf::RenderTarget &target);
    void drawHealth(sf::RenderTarget &target);
    void drawAmmo(sf::RenderTarget &target);
    void drawUI(sf::RenderTarget &target);
    //void handlePlayerEntitiesApproach();
    void updateEntities(sf::Time deltaT);
    void updateEnemies(sf::Time deltaT);
    //void setWeaponState(int state);

public:
    Game();
    Game(std::string fileName);
    void handleDrawing(sf::RenderTarget &target);
    void onUpdate(sf::Time deltaT);
    int checkGameState();
    ~Game();
};
