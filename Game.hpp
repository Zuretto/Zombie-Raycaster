#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include "Player.hpp"
#include"Map.hpp"
class Game{
private:
    //sf::Image wallImages[8]; //table consisting of images
    sf::Texture wallTexturesPx[8][texWidth]; //table consisting of 1-pixel wide textures
public:
    void drawScene(sf::RenderTarget & target, Player *player, Map *worldMap);
    Game();
};