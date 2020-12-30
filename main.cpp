#undef main
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <memory>
#include <iostream>
#include <experimental/optional>
#include <math.h>
#include <string>
#include "definitions.hpp"
#include "Player.hpp"
#include "Weapon.hpp"
#include "Game.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "Map.hpp"

int main(){

    Player *player = new Player(11, 11, -1, 0, M_PI/2);
    Game game(player);
    sf::RenderWindow window3D(sf::VideoMode(casterWidth, casterHeight), "ray casting");
    sf::Clock fpsClock;         fpsClock.restart();

    while (window3D.isOpen()){
        sf::Time deltaT = fpsClock.getElapsedTime();
        fpsClock.restart();
        std::cout << 1 / deltaT.asSeconds() << std::endl;
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
        window3D.clear();
        game.drawScene(window3D);
        game.drawSprites(window3D);
        game.drawWeapon(window3D);
        window3D.display();
        game.onUpdate(deltaT);
    }
    return 0;
}

/*
    to-do list:
    enemies attacks
    guns
*/