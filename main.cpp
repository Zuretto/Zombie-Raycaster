#undef main
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include "definitions.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Game.hpp"

int main(){
    Game game;
    Map *map = new Map("test.map");
    auto map_vect = map->getMapVector();
    Player *player = new Player(5, 5, -1, 0, 0, 1, map);
    //sf::RenderWindow window2D(sf::VideoMode(screenWidth, screenHeight), "cialo");
    sf::RenderWindow window3D(sf::VideoMode(casterWidth, casterHeight), "ray casting");
    sf::Clock clock;
    clock.restart();
    while (window3D.isOpen()) {
        sf::Time deltaT = clock.getElapsedTime();
        std::cout << 1 / deltaT.asSeconds() << std::endl;
        clock.restart();
        sf::Event e;
        while (window3D.pollEvent(e)) {
            switch (e.type) {
            case sf::Event::EventType::Closed:
                window3D.close();
                break;
            default:
                break;
            }
        }
        window3D.clear();
        game.drawScene(window3D, player, map);
        window3D.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player->forward(deltaT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player->backward(deltaT);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            player->rotateRight(deltaT);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            player->rotateLeft(deltaT);
        }
    }
    return 0;
}