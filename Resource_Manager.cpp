#include "Resource_Manager.hpp"
#include <iostream>
Resource_Manager::Resource_Manager(){

    sf::Image wallImages[8];
        wallImages[0].loadFromFile("data/pics/wooden plank.png");
        wallImages[1].loadFromFile("data/pics/chiseled stone brick.png");
        wallImages[2].loadFromFile("data/pics/cobblestone.png");
        wallImages[3].loadFromFile("data/pics/cracked stone brick.png"); 
        wallImages[4].loadFromFile("data/pics/nether brick.png");
        wallImages[5].loadFromFile("data/pics/stone brick.png");
        wallImages[6].loadFromFile("data/pics/stone.png");
        wallImages[7].loadFromFile("data/pics/andesite.png");
    for (int iType = 0; iType < 8; iType++){
        for (int jStripe = 0; jStripe < texWidth; jStripe++)
            wallTexturesPx[iType][jStripe].loadFromImage(wallImages[iType], sf::IntRect(jStripe, 0, 1, texHeight));
    }

    sf::Image entityImages[ENTITY_TYPES_NUMBER];
        entityImages[ENTITY].loadFromFile("data/pics/blank_entity.png");
        entityImages[BARREL].loadFromFile("data/pics/barrel.png");
        entityImages[AMMO_PISTOL].loadFromFile("data/pics/ammo_pistol.png");
        entityImages[AMMO_SHOTGUN].loadFromFile("data/pics/ammo_shotgun.png");
        entityImages[PILLAR].loadFromFile("data/pics/pillar.png");
    for (int iType = 0; iType < ENTITY_TYPES_NUMBER; iType++)
        for(int jStripe = 0; jStripe < entityWidth; jStripe++)
            entityTexturesPx[iType][jStripe].loadFromImage(entityImages[iType], sf::IntRect(jStripe, 0, 1, entityHeight));

    sf::Image enemyImages[ENEMY_TYPES_NUMBER];
        enemyImages[ENEMY].loadFromFile("data/pics/blank_enemy.png");
        enemyImages[ZOMBIE].loadFromFile("data/pics/zombie.png");
        enemyImages[SKELETON].loadFromFile("data/pics/skeleton.png");
    for(int type = 0; type < ENEMY_TYPES_NUMBER; type++){
        for(int state = 0; state < ENEMY_STATES_NUMBER; state++){
            for(int stripe = 0; stripe < enemyWidth; stripe++){
                enemyTexturesPx[type][state][stripe].loadFromImage(enemyImages[type], sf::IntRect(state*enemyWidth+stripe, 0, 1, entityHeight));
            }
        }
    }
    //WEAPON, FIST, PISTOL, SHOTGUN
    sf::Image weaponImages[WEAPON_TYPES_NUMBER];
        weaponImages[WEAPON].loadFromFile("data/pics/pistol.png");
        weaponImages[FIST].loadFromFile("data/pics/fist.png");
        weaponImages[PISTOL].loadFromFile("data/pics/pistol.png");
        weaponImages[SHOTGUN].loadFromFile("data/pics/shotgun.png");
    /*
    weaponTextures[PISTOL][DRAWN].loadFromImage(weaponImages[PISTOL], sf::IntRect(0, 0, 128, 128));
    weaponTextures[PISTOL][SHOT1].loadFromImage(weaponImages[PISTOL], sf::IntRect(128, 0, 128, 128));
    weaponTextures[PISTOL][SHOT2].loadFromImage(weaponImages[PISTOL], sf::IntRect(256, 0, 128, 128));
    weaponTextures[PISTOL][SHOT3].loadFromImage(weaponImages[PISTOL], sf::IntRect(384, 0, 128, 128));
    */
    for(int i = 0; i < WEAPON_TYPES_NUMBER; i++){
        for(int j = 0; j < WEAPON_STATES_NUMBER; j++){
            weaponTextures[i][j].loadFromImage(weaponImages[i], sf::IntRect(j * weaponWidth, 0, weaponWidth, weaponHeight));
        }
    }

    gameUIFont.loadFromFile("data/fonts/dum1.ttf");

    //for(int iType = 0; iType < WEAPON_TYPES_NUMBER; iType++){
    //    for(int jState = 0; jState < WEAPON_STATES_NUMBER; jState++){
    //        std::cout << jState * weaponWidth << std::endl;
    //        weaponTextures[iType][jState].loadFromImage(enemyImages[iType], sf::IntRect(jState * weaponWidth, 0, weaponWidth, weaponHeight));
    //    }
    //}
}

/*
sf::Texture *Resource_Manager::getWallTexture(int type, int stripe){
    return &wallTexturesPx[type][stripe];
}
sf::Texture *Resource_Manager::getEntityTexture(int type, int stripe){
    return &entityTexturesPx[type][stripe];
}
sf::Texture *Resource_Manager::getEnemyTexture(int type, int state, int stripe){
    return &enemyTexturesPx[type][state][stripe];
}
sf::Texture *Resource_Manager::getWeaponTexture(int type, int state){
    return &weaponTextures[type][state];
}
*/