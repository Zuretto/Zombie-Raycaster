#undef main
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Player.hpp"
#include "Map.hpp"
#define screenWidth 480
#define screenHeight 480


int main() {
    Map *map = new Map("test.map", screenWidth, screenHeight);
    double posX = 22, posY = 12;  //x and y start position
    double dirX = -1, dirY = 0; //initial direction vector
    Player *player = new Player(20, 20, 0.5, 0.5, 0, 0.66, map);
    sf::RenderWindow window2D(sf::VideoMode(screenWidth, screenHeight), "Hello World SFML Window");
    
    sf::Clock clock;
    clock.restart();
    while (window2D.isOpen()) {
        sf::Time deltaT = clock.getElapsedTime();
        //std::cout << deltaT.asSeconds() << std::endl;
        clock.restart();
        sf::Event e;
        while (window2D.pollEvent(e)) {
            switch (e.type) {
            case sf::Event::EventType::Closed:
                window2D.close();
                break;
            default:
                break;
            }
        }
        window2D.clear();
        window2D.draw(*map);
        //map->draw(window2D, screenWidth, screenHeight);
        
        window2D.draw(*player);
        window2D.display();
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