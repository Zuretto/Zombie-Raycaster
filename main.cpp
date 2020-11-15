#undef main
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Player.hpp"
#include "Map.hpp"
#define casterWidth 1024
#define casterHeight 720
#define texWidth 32
#define texHeight 32

int main() {
    Map *map = new Map("test.map");
    auto map_vect = map->getMapVector();
    Player *player = new Player(5, 5, -1, 0, 0, 1, map);
    //sf::RenderWindow window2D(sf::VideoMode(screenWidth, screenHeight), "cialo");
    sf::RenderWindow window3D(sf::VideoMode(casterWidth, casterHeight), "ray casting");
    sf::Clock clock;
    clock.restart();
    while ( window3D.isOpen()) {
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
        sf::RectangleShape sky(sf::Vector2f(casterWidth, casterHeight / 2));
        sky.setFillColor(sf::Color(108, 158, 222));
        window3D.draw(sky);
        sf::RectangleShape floor(sf::Vector2f(casterWidth, casterHeight / 2));
        floor.move(0, casterHeight/2);
        floor.setFillColor(sf::Color(56, 68, 82));
        window3D.draw(floor);

        std::vector<sf::Texture> texture[8];

        for(int x = 0; x < casterWidth; x++){
            //calculate ray position and direction
            double cameraX = 2 * x / (double)casterWidth - 1; //-1 for left pixel, 1 for right pixel
            double rayDirX = player->getdirX() + player->getplaneX() * cameraX;
            double rayDirY = player->getdirY() + player->getplaneY() * cameraX;
            //which box of the map we're in
            int mapX = int(player->getPosX());
            int mapY = int(player->getPosY());
            // length of ray from one x or y-side to next x or y-side
            // "1" is for the length of vector [rayDirX, rayDirY].
            double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : std::abs(1 / rayDirX)); 
            double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : std::abs(1 / rayDirY));
            //length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;
            //what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;
            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?
            //calculate step and initial sideDist
            if(rayDirX < 0){
                stepX = -1;
                sideDistX = (player->getPosX() - mapX) * deltaDistX;
            }
            else{
                stepX = 1;
                sideDistX = (mapX + 1.0 - player->getPosX()) * deltaDistX;
            }
            if(rayDirY < 0){
                stepY = -1;
                sideDistY = (player->getPosY() - mapY) * deltaDistY;
            }
            else{
                stepY = 1;
                sideDistY = (mapY + 1.0 - player->getPosY()) * deltaDistY;
            }
            //perform DDA
            while (hit == 0){
                //jump to next map square, OR in x-direction, OR in y-direction
                if(sideDistX < sideDistY){
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
                }
                else{
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
                }
                //Check if ray has hit a wall
                if(map_vect[mapX][mapY] > 0) hit = 1;
            }
            //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
            double perpWallDist;
            if(side == 0) perpWallDist = (mapX - player->getPosX() + (1 - stepX) / 2) / rayDirX;
            else          perpWallDist = (mapY - player->getPosY() + (1 - stepY) / 2) / rayDirY;
            //Calculate height of line to draw on screen
            int lineHeight = (int)(casterHeight / perpWallDist);
            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + casterHeight / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + casterHeight / 2;
            if (drawEnd >= casterHeight) drawEnd = casterHeight - 1;
            //choose wall color
            sf::Color color;
            switch(map_vect[mapX][mapY]){
                case 1:  color = sf::Color::Magenta;    break; //red
                case 2:  color = sf::Color::Cyan;       break; //green
                case 3:  color = sf::Color::Blue;       break; //blue
                case 4:  color = sf::Color::Red;        break; //white
                case 5:  color = sf::Color::Red;        break;
                case 6:  color = sf::Color::Red;        break;
                default: color = sf::Color::Yellow;     break; //yellow
            }
            //give x and y sides different brightness
            if(side == 1) {color.r /= 2; color.g /= 2; color.b /= 2;}
            //draw the pixels of the stripe as a vertical line
            sf::Vertex line[] ={
                sf::Vertex(sf::Vector2f(x, drawEnd), color),
                sf::Vertex(sf::Vector2f(x, drawStart), color)
            };
            window3D.draw(line, 2, sf::Lines);
        }


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