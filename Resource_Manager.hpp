#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "definitions.hpp"

class Resource_Manager{
private:
    sf::Texture wallTexturesPx[8][texWidth]; //table consisting of 1-pixel wide textures
    sf::Texture entityTexturesPx[ENTITY_TYPES_NUMBER][entityWidth];
    sf::Texture enemyTexturesPx[ENEMY_TYPES_NUMBER][ENEMY_STATES_NUMBER][enemyWidth];
    sf::Texture weaponTextures[GUN_TYPES_NUMBER][weapon_states];
public:
    Resource_Manager();
    sf::Texture getWallTexture(int type, int stripe);
    sf::Texture getEntityTexture(int type, int stripe);
    sf::Texture getEnemyTexture(int type, int state, int stripe);
    sf::Texture getWeaponTexture(int type, int state);
};