#include "Player.hpp"

Player::Player(double xpos, double ypos, double xdir, double ydir, double xplane, double yplane, Map *worldMap){
    moveSpeed = 100;
    radius = 10;
    posX = xpos;
    posY = ypos;
    dirX = xdir;
    dirY = ydir;
    planeX = xplane;
    planeY = yplane;
    map = worldMap;
    shape = new sf::CircleShape;
    shape->setRadius(radius);
    shape->setPosition(posX, posY);
    shape->setFillColor(sf::Color::Magenta);
}
double Player::getPosX(){
    return posX;
}
double Player::getposY(){
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
    shape = nullptr;
    std::cout<<"aaaaaaaaa";
}
void Player::forward(sf::Time deltaT){
    double discreteTime = deltaT.asSeconds();
    std::vector <std::vector <int>> map_vect = map->getMapVector();
    int futureYType = map_vect[int((posY + dirY * moveSpeed * discreteTime) / (map->pixelHeight() / map->height()))][int(posX / (map->pixelWidth() / map->width()))];
    int futureXType = map_vect[int(posY / (map->pixelHeight() / map->height()))][int((posX + dirX * moveSpeed * discreteTime) / (map->pixelWidth() / map->width()))];
    if(futureXType == 0) posX += dirX * moveSpeed * deltaT.asSeconds();
    if(futureYType == 0) posY += dirY * moveSpeed * deltaT.asSeconds();
    std::cout << posX << " " << posY << std::endl;
}
void Player::backward(sf::Time deltaT){
    double discreteTime = deltaT.asSeconds();
    std::vector <std::vector <int>> map_vect = map->getMapVector();
    int futureYType = map_vect[int((posY - dirY * moveSpeed * discreteTime) / (map->pixelHeight() / map->height()))][int(posX / (map->pixelWidth() / map->width()))];
    int futureXType = map_vect[int(posY / (map->pixelHeight() / map->height()))][int((posX - dirX * moveSpeed * discreteTime) / (map->pixelWidth() / map->width()))];
    if(futureXType == 0) posX -= dirX * moveSpeed * deltaT.asSeconds();
    if(futureYType == 0) posY -= dirY * moveSpeed * deltaT.asSeconds();
    std::cout << posX << " " << posY << std::endl;
}
void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const{
    shape->setPosition(posX, posY);
    target.draw(*shape, states);
}