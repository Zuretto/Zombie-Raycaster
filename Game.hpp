#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Entity.hpp"
class Game{
private:
    //sf::Image wallImages[8]; //table consisting of images
    sf::Texture wallTexturesPx[8][texWidth]; //table consisting of 1-pixel wide textures
    sf::Texture barrelTexturePx;
public:
    Game();
    void drawScene(sf::RenderTarget & target, Player *player, Map *worldMap);
    void drawEntities(sf::RenderTarget &target, Player *player, Map *worldMap, Entity *entity);
};
