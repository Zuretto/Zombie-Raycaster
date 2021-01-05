#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <memory>
#include <iostream>
#include "definitions.hpp"
#include "Player.hpp"
#include "Weapon.hpp"
#include "Game.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "Map.hpp"
#include "Resource_Manager.hpp"

#define NUMBER_OF_LEVELS 3
enum menu_bars {START, OPTIONS, EXIT, MENU_BARS_COUNT};
enum options_bars {LEVEL, BACK, OPTIONS_BARS_COUNT};
enum endscreen_bars {PLAY_AGAIN, END, END_SCREEN_BARS_COUNT};

class Menu{
private:
    const std::string levels[NUMBER_OF_LEVELS] = {"data/maps/level1.map", "data/maps/level2.map", "data/maps/playground.map"};
    const double inputCooldown = 0.25;
    Game *game;
    Resource_Manager *resManager;
    int   selectedMenuBar;
    int   gameState;
    int   selectedOptionsBar;
    int   selectedEndScreenBar;
    int   selectedLevel;
    sf::Clock inputClock;
public:
    Menu();
    void drawMenu(sf::RenderTarget &target);
    void drawDefeatScreen(sf::RenderTarget &target);
    void drawVictoryScreen(sf::RenderTarget &target);
    void drawOptions(sf::RenderTarget &target);
    void updateMenu(sf::Time deltaT);
    void updateOptions(sf::Time deltaT);
    void updateEndScreen(sf::Time deltaT);
    void gameLoop();

};