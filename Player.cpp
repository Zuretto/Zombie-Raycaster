#include "Player.hpp"
Player::Player(double xpos, double ypos, double xdir, double ydir, double viewAngle){
    for(int i = 0; i < WEAPON_TYPES_NUMBER; i++){
        weapons[i] = std::shared_ptr<Weapon>(new Weapon());
    }
    weapons[FIST] = std::shared_ptr<Fist>(new Fist());
    weapons[PISTOL] = std::shared_ptr<Pistol>(new Pistol());
    weapons[SHOTGUN] = std::shared_ptr<Shotgun>(new Shotgun());
    drawnWeapon = PISTOL;
    healthPoints = 100;
    radius = 0.25;
    posX = xpos;
    posY = ypos;
    moveSpeed = 10;
    rotationSpeed = 5;
    dirX = xdir;
    dirY = ydir;
    planeX = dirX * cos(-viewAngle) - dirY * sin(-viewAngle);
    planeY = dirX * sin(-viewAngle) + dirY * cos(-viewAngle);
    
}
double Player::getPosX(){
    return posX;
}
double Player::getPosY(){
    return posY;
}
double Player::getdirX(){
    return dirX;
}
double Player::getdirY(){
    return dirY;
}
double Player::getplaneX(){
    return planeX;
}
double Player::getplaneY(){
    return planeY;
}
double Player::getRadius(){
    return radius;
}
int Player::getDrawnWeapon(){
    return drawnWeapon;
}
double Player::getMoveSpeed(){
    return moveSpeed;
}
void Player::increaseHp(double heal){
    healthPoints += heal;
    if (healthPoints > 100) healthPoints = 100;
}
void Player::decreaseHp(double damage){
    healthPoints -= damage;
}
double Player::getCurrentHp(){
    return healthPoints;
}
double Player::getMaxHp(){
    return maxHealthPoints;
}
int Player::getDrawnWeaponAmmo(){
    return weapons[drawnWeapon]->getAmmo();
}
void Player::increaseAmmo(int weapon_type, int amount){
    weapons[weapon_type]->increaseAmmo(amount);
}

Player::~Player(){
    //std::cout << "deleted player." << std::endl;
}
int Player::getWeaponState(){
    return weapons[drawnWeapon]->calculateState();
}
void Player::forward(sf::Time deltaT, Map *worldMap, std::vector <std::shared_ptr<Entity>> entities){
    double discreteTime = deltaT.asSeconds();
    double xRadius = -radius * ((dirX < 0) - (0 < dirX));
    double yRadius = -radius * ((dirY < 0) - (0 < dirY));
    double futureX = posX + xRadius + dirX * moveSpeed * discreteTime;
    double futureY = posY + yRadius + dirY * moveSpeed * discreteTime;
    std::vector <std::vector <int>> map_vect = worldMap->getMapVector();
    if(map_vect[int(futureX)][int(posY + yRadius)] == false) posX += dirX * moveSpeed * discreteTime;
    if(map_vect[int(posX + xRadius)][int(futureY)] == false) posY += dirY * moveSpeed * discreteTime;
}
void Player::backward(sf::Time deltaT, Map *worldMap, std::vector <std::shared_ptr<Entity>> entities){
    double discreteTime = deltaT.asSeconds();
    std::vector <std::vector <int>> map_vect = worldMap->getMapVector();
    double xRadius = radius * ((dirX < 0) - (0 < dirX));
    double yRadius = radius * ((dirY < 0) - (0 < dirY));
    if(map_vect[int(posX + xRadius - dirX * moveSpeed * discreteTime)][int(posY + yRadius)] == false) posX -= dirX * moveSpeed * discreteTime;
    if(map_vect[int(posX + xRadius)][int(posY + yRadius - dirY * moveSpeed * discreteTime)] == false) posY -= dirY * moveSpeed * discreteTime;
}
void Player::rotateRight(sf::Time deltaT, Map *worldMap){
    //both camera direction and camera plane must be rotated
    double rSpeed = rotationSpeed * deltaT.asSeconds();
    double oldDirX = dirX;
    dirX = dirX * cos(-rSpeed) - dirY * sin(-rSpeed);
    dirY = oldDirX * sin(-rSpeed) + dirY * cos(-rSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(-rSpeed) - planeY * sin(-rSpeed);
    planeY = oldPlaneX * sin(-rSpeed) + planeY * cos(-rSpeed);
}
void Player::rotateLeft(sf::Time deltaT, Map *worldMap){
    //both camera direction and camera plane must be rotated
    double rSpeed = rotationSpeed * deltaT.asSeconds();
    double oldDirX = dirX;
    dirX = dirX * cos(rSpeed) - dirY * sin(rSpeed);
    dirY = oldDirX * sin(rSpeed) + dirY * cos(rSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(rSpeed) - planeY * sin(rSpeed);
    planeY = oldPlaneX * sin(rSpeed) + planeY * cos(rSpeed);
}

void Player::performShoot(Map *worldMap, std::vector <std::shared_ptr<Enemy>> &enemies){
    weapons[drawnWeapon]->performShoot(this, worldMap, enemies);
}

void Player::handleWeaponSwap(int weaponToChange){
    if(weapons[weaponToChange]->getType() != WEAPON){
        drawnWeapon = weaponToChange;
    }
}

