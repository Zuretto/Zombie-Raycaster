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
int Weapon::getAmmo(){
    return ammo;
}
void Weapon::increaseAmmo(int amount){
    std::cout << this->ammo << std::endl;
    std::cout << amount << std::endl;
    std::cout << this->ammo << " " << amount << std::endl;
    this->ammo += amount;
}
void Weapon::performShoot(Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> &enemies){
    if (weaponClock.getElapsedTime().asSeconds() > shotCooldown && this->ammo > 0){
        double step = 0.1; 
        double dirX = player->getdirX();
        double dirY = player->getdirY();
        double posX = player->getPosX();
        double posY = player->getPosY();
        std::vector <std::vector <int>> mapVect = worldMap->getMapVector();
        while(mapVect[posX][posY] == 0 && sqrt(pow(posX - player->getPosX(), 2) + pow(posY - player->getPosY(), 2)) < this->range){
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
        weaponClock.restart();
        this->ammo--;
    }
}

int Weapon::calculateState(){
    for(int i = 0; i < WEAPON_STATES_NUMBER; ++i){
        if (weaponClock.getElapsedTime().asSeconds() < shotCooldown * (i+1) / WEAPON_STATES_NUMBER){
            return (i + 1) % WEAPON_STATES_NUMBER;
        }
    }
    return DRAWN;
    /*
    if(weaponClock.getElapsedTime().asSeconds() < shotCooldown / 4){
        return SHOT1;
    }
    else if(weaponClock.getElapsedTime().asSeconds() < shotCooldown * 2 / 4){
        return SHOT2;
    }
    else if(weaponClock.getElapsedTime().asSeconds() < shotCooldown * 3 / 4){
        return SHOT3;
    }
    else return DRAWN;*/
}


Pistol::Pistol(){
    ammo = 10;
    damage = 40;
    range = 20;
    shotCooldown = 0.3;
    weaponClock.restart();
}
Pistol::~Pistol(){};
int Pistol::getType(){
    return PISTOL;
}
Shotgun::Shotgun(){
    ammo = 10;
    damage = 10;
    range = 10;
    shotCooldown = 1;
    weaponClock.restart();
}
Shotgun::~Shotgun(){}
int Shotgun::getType(){
    return SHOTGUN;
}
void Shotgun::performShoot(Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> &enemies){
    if (weaponClock.getElapsedTime().asSeconds() > shotCooldown && this->ammo > 0 ){
        double step = 0.1; 
        double planeX = player->getdirX() * cos(-shotAngle) - player->getdirY() * sin(-shotAngle);
        double planeY = player->getdirX() * sin(-shotAngle) + player->getdirY() * cos(-shotAngle);
        auto mapVect = worldMap->getMapVector();
        for(int x = 0; x < pelletNumber; x++){
            //calculate ray position and direction
            double cameraX = 2 * x / (double)pelletNumber - 1; //-1 for left pixel, 1 for right pixel
            double dirX = player->getdirX() + planeX * cameraX;
            double dirY = player->getdirY() + planeY * cameraX;
            double posX = player->getPosX();
            double posY = player->getPosY();
            while(mapVect[posX][posY] == 0 && sqrt(pow(posX - player->getPosX(), 2) + pow(posY - player->getPosY(), 2)) < this->range){
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
        this->ammo--;
        weaponClock.restart();
    }
}

Fist::Fist(){
    ammo = -1;
    damage = 25;
    range = 1;
    shotCooldown = 0.25;
    weaponClock.restart();
}
Fist::~Fist(){}
int Fist::getType(){
    return FIST;
}
void Fist::performShoot(Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> &enemies){
    if (weaponClock.getElapsedTime().asSeconds() > shotCooldown){
        double step = 0.1; 
        double dirX = player->getdirX();
        double dirY = player->getdirY();
        double posX = player->getPosX();
        double posY = player->getPosY();
        std::vector <std::vector <int>> mapVect = worldMap->getMapVector();
        while(mapVect[posX][posY] == 0 && sqrt(pow(posX - player->getPosX(), 2) + pow(posY - player->getPosY(), 2)) < this->range){
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
        weaponClock.restart();
    }
}