#undef main
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include "definitions.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Game.hpp"
#include "Entity.hpp"

int main(){
    Game game;
    Map *map = new Map("data/maps/test.map");
    auto map_vect = map->getMapVector();
    Player *player = new Player(10, 10, -1, 0, 0, 1, map);
    Entity *barrel = new Barrel(12, 13); 

    sf::RenderWindow window3D(sf::VideoMode(casterWidth, casterHeight), "ray casting");
    sf::Clock clock;
    clock.restart();
    while (window3D.isOpen()){
        sf::Time deltaT = clock.getElapsedTime();
        //std::cout << 1 / deltaT.asSeconds() << std::endl;
        clock.restart();
        sf::Event e;
        while (window3D.pollEvent(e)){
            switch (e.type) {
            case sf::Event::EventType::Closed:
                window3D.close();
                break;
            default:
                break;
            }
        }   
        //if(sqrt(pow(player->getPosX() - dynamic_cast <Barrel*>(barrel)->getPosX(), 2) + pow(player->getPosY() - dynamic_cast <Barrel*>(barrel)->getPosY(), 2)) < dynamic_cast <Barrel*>(barrel)->getRadius() + player->getRadius())
        //    std::cout << "bonk" << std::endl;
        
        window3D.clear();
        game.drawScene(window3D, player, map);
        game.drawEntities(window3D, player, map, barrel);
        window3D.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player->forward(deltaT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player->backward(deltaT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            player->rotateRight(deltaT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            player->rotateLeft(deltaT);
        }
    }
    return 0;
}

/*
    to-do list:
    rewrite Entity Drawing so that it comes back after wall drawing and checks if sth is on its way
    guns
    enemies
    








*/