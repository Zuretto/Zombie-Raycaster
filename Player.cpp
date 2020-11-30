#include "Player.hpp"
Player::Player(double xpos, double ypos, double xdir, double ydir, double xplane, double yplane){
    for(int i; i < GUN_TYPES_NUMBER; i++){
        weapons[i] = new Weapon();
    }
    weapons[PISTOL] = new Pistol();
    drawnGun = PISTOL;
    healthPoints = 100;
    radius = 0.25;
    posX = xpos;
    posY = ypos;
    moveSpeed = 10;
    rotationSpeed = 10;
    dirX = xdir;
    dirY = ydir;
    planeX = xplane;
    planeY = yplane;
    
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
    return drawnGun;
}
Player::~Player(){
    std::cout<<"aaaaaaaaa";
}
void Player::forward(sf::Time deltaT, Map *worldMap){
    double discreteTime = deltaT.asSeconds();
    double xRadius = -radius * ((dirX < 0) - (0 < dirX));
    double yRadius = -radius * ((dirY < 0) - (0 < dirY));
    std::vector <std::vector <int>> map_vect = worldMap->getMapVector();
    if(map_vect[int(posX + xRadius + dirX * moveSpeed * discreteTime)][int(posY + yRadius)] == false) posX += dirX * moveSpeed * discreteTime;
    if(map_vect[int(posX + xRadius)][int(posY + yRadius + dirY * moveSpeed * discreteTime)] == false) posY += dirY * moveSpeed * discreteTime;
}
void Player::backward(sf::Time deltaT, Map *worldMap){
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