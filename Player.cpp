#include "Player.hpp"
Player::Player(double xpos, double ypos, double xdir, double ydir, double xplane, double yplane, Map *worldMap){
    posX = xpos;
    posY = ypos;
    moveSpeed = 0.005;
    rotationSpeed = 0.001;
    dirX = xdir;
    dirY = ydir;
    planeX = xplane;
    planeY = yplane;
    this->worldMap = worldMap;
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
Player::~Player(){
    std::cout<<"aaaaaaaaa";
}
void Player::forward(sf::Time deltaT){
    double discreteTime = deltaT.asSeconds();
    std::vector <std::vector <int>> map_vect = worldMap->getMapVector();
    if(map_vect[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
    if(map_vect[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
}
void Player::backward(sf::Time deltaT){
    double discreteTime = deltaT.asSeconds();
    std::vector <std::vector <int>> map_vect = worldMap->getMapVector();
    if(map_vect[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    if(map_vect[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
}
void Player::rotateRight(sf::Time deltaT){
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(-rotationSpeed) - dirY * sin(-rotationSpeed);
      dirY = oldDirX * sin(-rotationSpeed) + dirY * cos(-rotationSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotationSpeed) - planeY * sin(-rotationSpeed);
      planeY = oldPlaneX * sin(-rotationSpeed) + planeY * cos(-rotationSpeed);
    }
void Player::rotateLeft(sf::Time deltaT){
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotationSpeed) - dirY * sin(rotationSpeed);
      dirY = oldDirX * sin(rotationSpeed) + dirY * cos(rotationSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotationSpeed) - planeY * sin(rotationSpeed);
      planeY = oldPlaneX * sin(rotationSpeed) + planeY * cos(rotationSpeed);
}