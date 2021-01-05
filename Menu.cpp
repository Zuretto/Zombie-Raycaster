#include "Menu.hpp"
Menu::Menu(){
    resManager = new Resource_Manager;
    game = new Game;
    gameState = IN_MENU;
    selectedMenuBar = START;
    selectedLevel = 0;
    selectedOptionsBar = BACK;
    selectedEndScreenBar = PLAY_AGAIN;
    inputClock.restart();
}

void Menu::drawMenu(sf::RenderTarget &target){
    sf::FloatRect textRect;
    sf::Text startText = sf::Text("START", resManager->menuUIFont, casterWidth / 8);
    textRect = startText.getLocalBounds();
    startText.move(casterWidth/2 - textRect.width/2, casterHeight/8*1);
    sf::Text optionsText = sf::Text("OPTIONS", resManager->menuUIFont, casterWidth / 8);
    textRect = optionsText.getLocalBounds();
    optionsText.move(casterWidth/2 - textRect.width/2, casterHeight/8*2);
    sf::Text exitText = sf::Text("EXIT", resManager->menuUIFont, casterWidth / 8);
    textRect = exitText.getLocalBounds();
    exitText.move(casterWidth/2 - textRect.width/2, casterHeight/8*3);
    if(selectedMenuBar == START) startText.setFillColor(sf::Color::Green);
    if(selectedMenuBar == OPTIONS) optionsText.setFillColor(sf::Color::Green);
    if(selectedMenuBar == EXIT) exitText.setFillColor(sf::Color::Green);
    target.draw(startText);
    target.draw(optionsText);
    target.draw(exitText);
}
void Menu::drawDefeatScreen(sf::RenderTarget &target){
    sf::FloatRect textRect;
    sf::Text looseText = sf::Text("YOU'VE LOST.", resManager->menuUIFont, casterWidth / 8);
    textRect = looseText.getLocalBounds();
    looseText.setFillColor(sf::Color::Red);
    looseText.move(casterWidth/2 - textRect.width/2, casterHeight/8 * 1);

    sf::Text playAgainText = sf::Text("PLAY AGAIN", resManager->menuUIFont, casterWidth / 8);
    textRect = playAgainText.getLocalBounds();
    playAgainText.move(casterWidth/2 - textRect.width/2, casterHeight/8*3);
    
    sf::Text exitText = sf::Text("EXIT", resManager->menuUIFont, casterWidth / 8);
    textRect = exitText.getLocalBounds();
    exitText.move(casterWidth/2 - textRect.width/2, casterHeight/8*5);
    
    if(selectedEndScreenBar == PLAY_AGAIN) playAgainText.setFillColor(sf::Color::Green);
    if(selectedEndScreenBar == END)        exitText.setFillColor(sf::Color::Green);
    
    target.draw(looseText);
    target.draw(playAgainText);
    target.draw(exitText);
}
void Menu::drawVictoryScreen(sf::RenderTarget &target){
    sf::FloatRect textRect;
    sf::Text victoryText = sf::Text("YOU'VE WON!", resManager->menuUIFont, casterWidth / 8);
    textRect = victoryText.getLocalBounds();
    victoryText.setFillColor(sf::Color::Green);
    victoryText.move(casterWidth/2 - textRect.width/2, casterHeight/8 * 1);
    
    sf::Text playAgainText = sf::Text("PLAY AGAIN", resManager->menuUIFont, casterWidth / 8);
    textRect = playAgainText.getLocalBounds();
    playAgainText.move(casterWidth/2 - textRect.width/2, casterHeight/8*3);
    
    sf::Text exitText = sf::Text("EXIT", resManager->menuUIFont, casterWidth / 8);
    textRect = exitText.getLocalBounds();
    exitText.move(casterWidth/2 - textRect.width/2, casterHeight/8*5);
    
    if(selectedEndScreenBar == PLAY_AGAIN) playAgainText.setFillColor(sf::Color::Green);
    if(selectedEndScreenBar == END)        exitText.setFillColor(sf::Color::Green);
    
    target.draw(victoryText);
    target.draw(playAgainText);
    target.draw(exitText);
}

void Menu::drawOptions(sf::RenderTarget &target){
    sf::FloatRect textRect;
    std::string levelWholeName = levels[selectedLevel];
    std::size_t slashPos = levelWholeName.find_last_of("/");
    std::string levelWithExtension = levelWholeName.substr(slashPos + 1);
    std::size_t dotPos = levelWithExtension.find(".");
    std::string levelName = levelWithExtension.substr(0, dotPos);
    sf::Text levelText = sf::Text(levelName, resManager->menuUIFont, casterWidth / 8);
    textRect = levelText.getLocalBounds();
    levelText.move(casterWidth/2 - textRect.width/2, casterHeight/8*2);
    sf::Text backText = sf::Text("BACK", resManager->menuUIFont, casterWidth / 8);
    textRect = backText.getLocalBounds();
    backText.move(casterWidth/2 - textRect.width/2, casterHeight/8*4);
    if(selectedOptionsBar == LEVEL) levelText.setFillColor(sf::Color::Green);
    if(selectedOptionsBar == BACK)  backText.setFillColor(sf::Color::Green);
    target.draw(levelText);
    target.draw(backText);
}

void Menu::updateMenu(sf::Time deltaT){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && inputClock.getElapsedTime().asSeconds() > inputCooldown){
        selectedMenuBar = selectedMenuBar - 1 + (MENU_BARS_COUNT * (selectedMenuBar == 0));
        inputClock.restart();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && inputClock.getElapsedTime().asSeconds() > inputCooldown){
        selectedMenuBar = selectedMenuBar + 1 - (MENU_BARS_COUNT * (selectedMenuBar == 2));
        inputClock.restart();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && inputClock.getElapsedTime().asSeconds() > inputCooldown){
        if(selectedMenuBar == START){
            this->game = new Game(levels[selectedLevel]);
            gameState = IN_GAME;
            inputClock.restart();

        }
        else if(selectedMenuBar == OPTIONS){
            gameState = IN_OPTIONS;
            inputClock.restart();

        }
        else if(selectedMenuBar == EXIT){
            exit(0);
        }
    }
}
void Menu::updateOptions(sf::Time deltaT){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && inputClock.getElapsedTime().asSeconds() > inputCooldown){
        selectedOptionsBar = selectedOptionsBar - 1 + (OPTIONS_BARS_COUNT * (selectedOptionsBar == 0));
        inputClock.restart();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && inputClock.getElapsedTime().asSeconds() > inputCooldown){
        selectedOptionsBar = selectedOptionsBar + 1 - (OPTIONS_BARS_COUNT * (selectedOptionsBar == OPTIONS_BARS_COUNT - 1));
        inputClock.restart();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && inputClock.getElapsedTime().asSeconds() > inputCooldown){
        if(selectedOptionsBar == LEVEL){
            selectedLevel = selectedLevel + 1 - (NUMBER_OF_LEVELS * (selectedLevel == NUMBER_OF_LEVELS - 1));
            inputClock.restart();
        }
        if(selectedOptionsBar == BACK){
            gameState = IN_MENU;
            inputClock.restart();
        }
    }
}
void Menu::updateEndScreen(sf::Time deltaT){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && inputClock.getElapsedTime().asSeconds() > inputCooldown){
        selectedEndScreenBar = selectedEndScreenBar - 1 + (END_SCREEN_BARS_COUNT * (selectedEndScreenBar == 0));
        inputClock.restart();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && inputClock.getElapsedTime().asSeconds() > inputCooldown){
        selectedEndScreenBar = selectedEndScreenBar + 1 - (END_SCREEN_BARS_COUNT * (selectedEndScreenBar == END_SCREEN_BARS_COUNT - 1));
        inputClock.restart();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && inputClock.getElapsedTime().asSeconds() > inputCooldown){
        if(selectedEndScreenBar == PLAY_AGAIN){
            gameState = IN_MENU;
            inputClock.restart();
        }
        if(selectedEndScreenBar == END){
            exit(0);
            inputClock.restart();
        }
    }


}
void Menu::gameLoop(){
    sf::RenderWindow window3D(sf::VideoMode(casterWidth, casterHeight), "Zombie Raycaster");
    window3D.setMouseCursorVisible(false);
    window3D.setVerticalSyncEnabled(true);
    sf::Clock fpsClock;         fpsClock.restart();
    while (window3D.isOpen()){
        sf::Time deltaT = fpsClock.getElapsedTime();
        fpsClock.restart();
        //std::cout << 1 / deltaT.asSeconds() << std::endl;
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
        /*DRAWING PART*/
        window3D.clear();

        if(gameState == IN_MENU){
            drawMenu(window3D);
        }
        else if (gameState == IN_OPTIONS){
            drawOptions(window3D);
        }
        else if (gameState == IN_GAME){
            game->handleDrawing(window3D);
        }
        else if (gameState == WON){
            drawVictoryScreen(window3D);
        }
        else if (gameState == LOST){
            drawDefeatScreen(window3D);
        }

        window3D.display();

        /*UPDATE PART*/
        if(gameState == IN_MENU){
            updateMenu(deltaT);
        }
        else if(gameState == IN_OPTIONS){
            updateOptions(deltaT);
        }
        else if (gameState == IN_GAME){
            game->onUpdate(deltaT);
            gameState = game->checkGameState();
            if (gameState != IN_GAME) delete game;
        }
        else if(gameState == LOST){
            updateEndScreen(deltaT);
        }
        else if(gameState == WON){
            updateEndScreen(deltaT);
        }
    }
}