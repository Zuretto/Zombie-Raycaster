#include "Weapon.hpp"
Weapon::Weapon(){}
Weapon::~Weapon(){
    std::cout << "Deleted Weapon" << std::endl;
}
int Weapon::getType(){
    return WEAPON;
}
int Weapon::getDamage(){
    return damage;
}
int Weapon::getRange(){
    return range;
}
void Weapon::performShoot(Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> &enemies){
    double step = 0.1; 
    double dirX = player->getdirX();
    double dirY = player->getdirY();
    double posX = player->getPosX();
    double posY = player->getPosY();
    std::vector <std::vector <int>> mapVect = worldMap->getMapVector();
    while(mapVect[posX][posY] == 0){
        posX += dirX * step;
        posY += dirY * step;
        bool hitEnemy = 0;
        for(auto enemy : enemies){
            if(sqrt(pow(enemy->getPosX() - posX, 2) + pow(enemy->getPosY() - posY, 2)) < enemy->getRadius() && enemy->getHp() > 0){
                enemy->lowerHp(damage);
                std::cout << enemy->getHp() << std::endl;
                hitEnemy = 1;
                break;
            }
        }
        if (hitEnemy) break;
    }
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
