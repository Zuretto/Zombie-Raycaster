#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "definitions.hpp"

class Resource_Manager{
private:
    //Arrays containing textures or texture stripes
    sf::Texture wallTexturesPx[8][texWidth]; 
    sf::Texture entityTexturesPx[ENTITY_TYPES_NUMBER][entityWidth];
    sf::Texture enemyTexturesPx[ENEMY_TYPES_NUMBER][ENEMY_STATES_NUMBER][enemyWidth];
    sf::Texture weaponTextures[WEAPON_TYPES_NUMBER][WEAPON_STATES_NUMBER];
    sf::Font    gameUIFont;
    sf::Font    menuUIFont;
public:
    Resource_Manager();
    ~Resource_Manager();
    /* 
    sf::Texture *getWallTexture(int type, int stripe);
    sf::Texture *getEntityTexture(int type, int stripe);
    sf::Texture *getEnemyTexture(int type, int state, int stripe);
    sf::Texture *getWeaponTexture(int type, int state);
    */
    friend class Game;
    friend class Menu;
};