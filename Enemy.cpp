#include "Enemy.hpp"

Enemy::Enemy(){
}

Enemy::~Enemy(){
    //std::cout << "deleted Enemy" << std::endl;
}

int Enemy::getType(){
    return ENEMY;
}

double Enemy::getPosX() const {
    return posX;
}

double Enemy::getPosY() const {
    return posY;
}

double Enemy::getRadius(){
    return radius;
}

int Enemy::getHp(){
    return healthPoints;
}

void Enemy::lowerHp(unsigned int damage){
    healthPoints -= damage;
    if (healthPoints <= 0){
        this->deadClock.restart();
    }
}

bool Enemy::isPlayerBehindTheWall(Player *player, Map *worldmap){
    auto mapVect = worldmap->getMapVector();    
    double deltaX = -this->posX + player->getPosX();
    double deltaY = -this->posY + player->getPosY();
    double dist = sqrt(pow(deltaX, 2)+ pow(deltaY,2));
    double dirX = deltaX / dist;
    double dirY = deltaY / dist;
    double rayPosX = this->posX;
    double rayPosY = this->posY;
    double rayDist;
    double rayStep = 0.1;
    do{
        rayPosX += dirX * rayStep;
        rayPosY += dirY * rayStep;
        rayDist = sqrt(pow(rayPosX - player->getPosX(), 2) + pow(rayPosY - player->getPosY(), 2));
    } while (rayDist > this->radius + player->getRadius() && mapVect[int(rayPosX)][int(rayPosY)] == 0);
    if(rayDist < this->radius + player->getRadius()) return false;
    else return true;
}

bool Enemy::futurePoseXEnemyIntersection(std::vector <std::shared_ptr<Enemy>> enemies, double futureX){
    for(auto enemy : enemies){
        if(enemy->healthPoints > 0){
            double futureXDist = sqrt(pow(futureX - enemy->posX, 2) + pow(this->posY - enemy->posY, 2));
            if(futureXDist < this->radius + enemy->radius) {
                return false;
            }
        }
    }
    return true;
}

bool Enemy::futurePoseYEnemyIntersection(std::vector <std::shared_ptr<Enemy>> enemies, double futureY){
    for(auto enemy : enemies){
        if(enemy->healthPoints > 0){
            double futureYDist = sqrt(pow(this->posX - enemy->posX,2) + pow(futureY - enemy->posY, 2));
            if(futureYDist < this->radius + enemy->radius) return false;
        }
    }
    return true;
}

void Enemy::handleMoveLogic(sf::Time deltaT, Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> enemies){
    if (healthPoints > 0){
        auto map_vect = worldMap->getMapVector();
        double pathToWalk = this->moveSpeed * deltaT.asSeconds();
        double deltaX = -this->posX + player->getPosX();
        double deltaY = -this->posY + player->getPosY();
        double dist = sqrt(pow(deltaX, 2)+ pow(deltaY,2));
        if(dist > this->radius + player->getRadius()){
            double dirX = deltaX / dist;
            double dirY = deltaY / dist;
            double xRadius = -radius * ((dirX < 0) - (0 < dirX));
            double yRadius = -radius * ((dirY < 0) - (0 < dirY));
            double futureX = posX + xRadius + dirX * pathToWalk;
            double futureY = posY + yRadius + dirY * pathToWalk;
            if(map_vect[int(futureX)][int(posY + yRadius)] == 0 && futurePoseXEnemyIntersection(enemies, futureX) == true) posX += dirX * pathToWalk;
            if(map_vect[int(posX + xRadius)][int(futureY)] == 0 && futurePoseYEnemyIntersection(enemies, futureY) == true) posY += dirY * pathToWalk;
        }
    }
}
void Enemy::handleAttackLogic(Player* player, std::vector <std::shared_ptr<Entity>> &entities){
    if(healthPoints > 0 && activated == true && attackClock.getElapsedTime().asSeconds() >= attackCooldown){
        double distance = sqrt(pow(player->getPosX() - this->posX, 2)+ pow(player->getPosY() - this->posY,2));
        if(distance < 1){ //attack range = 1
            player->decreaseHp(damage);
            attackClock.restart();
        }
    }
}
void Enemy::handleLogic(sf::Time deltaT, Player *player, Map *worldMap, std::vector <std::shared_ptr<Enemy>> enemiesWithoutThis, std::vector <std::shared_ptr<Entity>> &entities){
    if(activated == false){
        if(!isPlayerBehindTheWall(player, worldMap)) activated = true;
    }
    else if(activated == true){
        handleMoveLogic(deltaT, player, worldMap, enemiesWithoutThis);
        handleAttackLogic(player, entities);
    }
}
int Enemy::calculateState(){
    if (healthPoints > 0){
        return ALIVE;
    }
    else{
        double deadSeconds = deadClock.getElapsedTime().asSeconds();
        if      (deadSeconds < 0.5) return DIED1;
        else if (deadSeconds < 1)   return DIED2;
        else                        return DEAD;
    }
}


Zombie::Zombie(double posX, double posY){
    this->activated = false;
    this->moveSpeed = 4;
    this->healthPoints = 150;
    this->posX = posX;
    this->posY = posY;
    this->radius = 0.4;
    this->damage = 25;
    this->attackClock.restart();
    this->attackCooldown = 1;
}

Zombie::~Zombie(){
}

int Zombie::getType(){
    return ZOMBIE;
}

Skeleton::Skeleton(double posX, double posY){
    this->activated = false;
    this->moveSpeed = 8;
    this->healthPoints = 75;
    this->posX = posX;
    this->posY = posY;
    this->radius = 0.1;
    this->damage = 10;
    this->attackClock.restart();
    this->attackCooldown = 0.75;
}
Skeleton::~Skeleton(){}
int Skeleton::getType(){
    return SKELETON;
}

FireWizard::FireWizard(double posX, double posY){
    this->activated = false;
    this->moveSpeed = 8;
    this->healthPoints = 50;
    this->posX = posX;
    this->posY = posY;
    this->radius = 0.4;
    this->damage = 0;
    this->attackClock.restart();
    this->attackCooldown = 2;
}
FireWizard::~FireWizard(){}
int FireWizard::getType(){
    return FIRE_WIZARD;
}
void FireWizard::handleAttackLogic(Player *player, std::vector <std::shared_ptr<Entity>> &entities){
    if(healthPoints > 0 && attackClock.getElapsedTime().asSeconds() >= attackCooldown){
        double deltaX = -this->posX + player->getPosX();
        double deltaY = -this->posY + player->getPosY();
        double dist = sqrt(pow(deltaX, 2)+ pow(deltaY,2));
        double dirX = deltaX / dist;
        double dirY = deltaY / dist;
        entities.push_back(std::shared_ptr<Fireball> (new Fireball(this->posX, this->posY, dirX, dirY)));
        attackClock.restart();
    }
}