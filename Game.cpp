#include "Game.hpp"
Game::Game(){
}
Game::Game(std::string fileName){
    worldMap = new Map(fileName);
    resManager = new Resource_Manager;

    //entities.push_back(std::shared_ptr<Barrel> (new Barrel(11,13)));
    //entities.push_back(std::shared_ptr<Barrel> (new Barrel(12,13)));
    //entities.push_back(std::shared_ptr<Pillar> (new Pillar(3,3)));
    //entities.push_back(std::shared_ptr<Barrel> (new Barrel(13,13)));
    //entities.push_back(std::shared_ptr<Ammo_Pistol> (new Ammo_Pistol(4,4)));
    //entities.push_back(std::shared_ptr<Ammo_Shotgun> (new Ammo_Shotgun(5,5)));
    //entities.push_back(std::shared_ptr<Hamburger> (new Hamburger(6,6)));
    //entities.push_back(std::shared_ptr<Soda> (new Soda(7,7)));
    //entities.push_back(std::shared_ptr<Fireball> (new Fireball(10, 10, 0, 1)));

    //enemies.push_back(std::shared_ptr<FireWizard> (new FireWizard(4,4)));
    //enemies.push_back(std::shared_ptr<Enemy> (new Skeleton(3,3)));
    //enemies.push_back(std::shared_ptr<Enemy> (new Skeleton(10,9)));
    //enemies.push_back(std::shared_ptr<Enemy> (new Skeleton(10,8)));
    //enemies.push_back(std::shared_ptr<Enemy> (new Skeleton(10,7)));
    //enemies.push_back(std::shared_ptr<Enemy> (new Skeleton(10,6)));
    //enemies.push_back(std::shared_ptr<Enemy> (new Skeleton(10,5)));
    //enemies.push_back(std::shared_ptr<Enemy> (new Zombie(10,4)));

    loadObjectsFromFile(fileName);
    spriteComp.structPlayer = player;

}
void Game::loadObjectsFromFile(std::string fileName){
    std::ifstream fp(fileName);
    if(!fp){
        std::cerr << "Failed to load map file " << fileName;
    }
    std::string strbuf;
    while (std::getline(fp, strbuf) && strbuf != "OBJECTS_LOADING:"){}
    while(std::getline(fp, strbuf)){
        std::stringstream sstream(strbuf);
        std::string objectName; sstream >> objectName;
        if(objectName == "PLAYER"){
            double posX, posY, dirX, dirY;
            sstream >> posY;
            sstream >> posX;
            sstream >> dirY;
            sstream >> dirX;
            player = new Player(posX, posY, dirX, dirY, M_PI/2);
        }
        else if(objectName == "ZOMBIE"){
            double posX, posY;
            sstream >> posY;
            sstream >> posX;
            enemies.push_back(std::shared_ptr<Enemy> (new Zombie(posX, posY)));
        }
        else if(objectName == "SKELETON"){
            double posX, posY;
            sstream >> posY;
            sstream >> posX;
            enemies.push_back(std::shared_ptr<Enemy> (new Skeleton(posX, posY)));
        }
        else if(objectName == "FIRE_WIZARD"){
            double posX, posY;
            sstream >> posY;
            sstream >> posX;
            enemies.push_back(std::shared_ptr<Enemy> (new FireWizard(posX, posY)));
        }
        else if(objectName == "BARREL"){
            double posX, posY;
            sstream >> posY;
            sstream >> posX;
            entities.push_back(std::shared_ptr<Barrel>(new Barrel(posX, posY)));
        }
        else if(objectName == "PILLAR"){
            double posX, posY;
            sstream >> posY;
            sstream >> posX;
            entities.push_back(std::shared_ptr<Pillar>(new Pillar(posX, posY)));
        }
        else if(objectName == "AMMO_PISTOL"){
            double posX, posY;
            sstream >> posY;
            sstream >> posX;
            entities.push_back(std::shared_ptr<Ammo_Pistol>(new Ammo_Pistol(posX, posY)));
        }
        else if(objectName == "AMMO_SHOTGUN"){
            double posX, posY;
            sstream >> posY;
            sstream >> posX;
            entities.push_back(std::shared_ptr<Ammo_Shotgun>(new Ammo_Shotgun(posX, posY)));
        }
        else if(objectName == "SODA"){
            double posX, posY;
            sstream >> posY;
            sstream >> posX;
            entities.push_back(std::shared_ptr<Soda>(new Soda(posX, posY)));
        }
        else if(objectName == "HAMBURGER"){
            double posX, posY;
            sstream >> posY;
            sstream >> posX;
            entities.push_back(std::shared_ptr<Hamburger>(new Hamburger(posX, posY)));
        }
    }
}

bool Game::checkIfAllEnemiesAreDead(){
    for(auto enemy : enemies){
        if (enemy->getHp() > 0) return false;
    }
    return true;
}
void Game::drawScene(sf::RenderTarget &target){
    sf::RectangleShape sky(sf::Vector2f(casterWidth, casterHeight / 2));
    sky.setFillColor(sf::Color(108, 158, 222));
    target.draw(sky);
    sf::RectangleShape floor(sf::Vector2f(casterWidth, casterHeight / 2));
    floor.move(0, casterHeight/2);
    floor.setFillColor(sf::Color(56, 68, 82));
    target.draw(floor);
    auto map_vect = worldMap->getMapVector();
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
        //SET THE ZBUFFER FOR THE SPRITE CASTING
        ZBuffer[x] = perpWallDist; //perpendicular distance is used
        //Calculate height of line to draw on screen
        int lineHeight = (int)(casterHeight / perpWallDist);
        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + casterHeight / 2;
        //texturing calculations
        int texNum = map_vect[mapX][mapY] - 1;          //texture number
        double wallX;                                   //where exactly the wall was hit
        if (side == 0) wallX = player->getPosY() + perpWallDist * rayDirY;
        else           wallX = player->getPosX() + perpWallDist * rayDirX;
        wallX -= std::floor(wallX);
        int textureX = int(wallX * texWidth);           //x coordinate on the texture
        //Drawing
        sf::Sprite lineSprite(resManager->wallTexturesPx[texNum][textureX]);
        lineSprite.setScale(1, (double)lineHeight/texHeight); //stretches line of pixels to the bottom
        lineSprite.move(x, drawStart);
        target.draw(lineSprite);
    }
}

void Game::drawEntity(sf::RenderTarget &target, std::shared_ptr<Entity> &entity){
    //translate sprite position to relative to camera
            double spriteX = entity->getPosX() - player->getPosX();
            double spriteY = entity->getPosY() - player->getPosY();;
            //transform sprite with the inverse camera matrix
            // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
            // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
            // [ planeY   dirY ]                                          [ -planeY  planeX ]
            double invDet = 1.0 / (player->getplaneX() * player->getdirY() - player->getdirX() * player->getplaneY()); //required for correct matrix multiplication
            //this is actually the depth inside the screen, that what Z is   in 3D
            double transformX = invDet * (player->getdirY() * spriteX - player->getdirX() * spriteY);
            double transformY = invDet * (-player->getplaneY() * spriteX + player->getplaneX() * spriteY); 
            int spriteScreenX = int((casterWidth / 2) * (1 + transformX / transformY));
            //calculate height of the sprite on screen
            int spriteHeight = abs(int(casterHeight / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
            //calculate lowest and highest pixel to fill in current stripe
            int drawStartY = -spriteHeight / 2 + casterHeight / 2;
            //if(drawStartY < 0) drawStartY = 0;
            int drawEndY = spriteHeight / 2 + casterHeight / 2;
            //if(drawEndY >= casterHeight) drawEndY = casterHeight - 1;
            //calculate width of the sprite
            int spriteWidth = abs(int (casterHeight / (transformY)));
            int drawStartX = -spriteWidth / 2 + spriteScreenX;
            if(drawStartX < 0) drawStartX = 0;
            int drawEndX = spriteWidth / 2 + spriteScreenX;
            if(drawEndX >= casterWidth) drawEndX = casterWidth - 1;
            for(int stripe = drawStartX; stripe < drawEndX; stripe++){
                int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * entityWidth / spriteWidth) / 256;
                if(transformY > 0 && stripe > 0 && stripe < casterWidth && transformY < ZBuffer[stripe]){
                    sf::Sprite lineSprite(resManager->entityTexturesPx[entity->getType()][texX]);
                    lineSprite.setScale(1, (double)(drawEndY - drawStartY)/entityHeight); //stretches line of pixels to the bottom
                    lineSprite.move(stripe, drawStartY);
                    target.draw(lineSprite);
                }
            }
}

void Game::drawEnemy(sf::RenderTarget &target, std::shared_ptr<Enemy> &enemy){
    //translate sprite position to relative to camera
    double spriteX = enemy->getPosX() - player->getPosX();
    double spriteY = enemy->getPosY() - player->getPosY();;
    //transform sprite with the inverse camera matrix
    // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
    // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
    // [ planeY   dirY ]                                          [ -planeY  planeX ]
    double invDet = 1.0 / (player->getplaneX() * player->getdirY() - player->getdirX() * player->getplaneY()); //required for correct matrix multiplication
    //this is actually the depth inside the screen, that what Z is   in 3D
    double transformX = invDet * (player->getdirY() * spriteX - player->getdirX() * spriteY);
    double transformY = invDet * (-player->getplaneY() * spriteX + player->getplaneX() * spriteY); 
    int spriteScreenX = int((casterWidth / 2) * (1 + transformX / transformY));
    //calculate height of the sprite on screen
    int spriteHeight = abs(int(casterHeight / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
    //calculate lowest and highest pixel to fill in current stripe
    int drawStartY = -spriteHeight / 2 + casterHeight / 2;
    //if(drawStartY < 0) drawStartY = 0;
    int drawEndY = spriteHeight / 2 + casterHeight / 2;
    //if(drawEndY >= casterHeight) drawEndY = casterHeight - 1;
    //calculate width of the sprite
    int spriteWidth = abs(int (casterHeight / (transformY)));
    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    if(drawStartX < 0) drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if(drawEndX >= casterWidth) drawEndX = casterWidth - 1;
    for(int stripe = drawStartX; stripe < drawEndX; stripe++){
        int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * enemyWidth / spriteWidth) / 256;
        if(transformY > 0 && stripe > 0 && stripe < casterWidth && transformY < ZBuffer[stripe]){
            sf::Sprite lineSprite(resManager->enemyTexturesPx[enemy->getType()][enemy->calculateState()][texX]);
            lineSprite.setScale(1, (double)(drawEndY - drawStartY)/enemyHeight); //stretches line of pixels to the bottom
            lineSprite.move(stripe, drawStartY);
            target.draw(lineSprite);
        }
    }
}

void Game::drawSprites(sf::RenderTarget &target){
    //sorting the entities & enemies
    std::sort(entities.begin(), entities.end(), spriteComp);
    std::sort(enemies.begin(), enemies.end(), spriteComp);
    int i_entity = 0;
    int i_enemy = 0;
    for(; i_entity < entities.size() || i_enemy < enemies.size();){
        if(i_enemy >= enemies.size()){
            drawEntity(target, entities[i_entity]);
            i_entity++;
        }
        else if (i_entity >= entities.size()){
            drawEnemy(target, enemies[i_enemy]);
            i_enemy++;
        }
        else if (pow(entities[i_entity]->getPosX() - player->getPosX(), 2) + pow(entities[i_entity]->getPosY() - player->getPosY(), 2) 
            >=   pow(enemies[i_enemy]->getPosX() - player->getPosX(), 2) + pow(enemies[i_enemy]->getPosY() - player->getPosY(), 2)){
            drawEntity(target, entities[i_entity]);
            i_entity++;
        }
        else{
            drawEnemy(target, enemies[i_enemy]);
            i_enemy++;
        }
    }
}

void Game::drawWeapon(sf::RenderTarget &target){
    sf::Sprite gunSprite(resManager->weaponTextures[player->getDrawnWeapon()][player->getWeaponState()]);
    double scaleX = (double)casterWidth*2/5/weaponWidth;
    double scaleY = (double)casterHeight*2/5/weaponHeight;
    gunSprite.setScale(scaleX, scaleY);
    gunSprite.move(casterWidth/2 - scaleX * weaponWidth/2, casterHeight - scaleY * weaponHeight);
    target.draw(gunSprite);
}

void Game::drawHealth(sf::RenderTarget &target){
    sf::Text healthText;
    healthText.setFont(resManager->gameUIFont);
    healthText.setString(std::to_string((int)player->getCurrentHp()));
    healthText.setCharacterSize(casterHeight/5);
    healthText.setFillColor(sf::Color::Red);
    healthText.move(0, casterHeight - healthText.getCharacterSize());
    target.draw(healthText);
}

void Game::drawAmmo(sf::RenderTarget &target){
    sf::Text ammoText;
    int weaponAmmo = player->getDrawnWeaponAmmo();
    if(weaponAmmo >= 0){
        ammoText.setFont(resManager->gameUIFont);
        ammoText.setString(std::to_string(weaponAmmo));
        ammoText.setCharacterSize(casterHeight/5);
        ammoText.setFillColor(sf::Color::Yellow);
        ammoText.move(0, casterHeight - ammoText.getCharacterSize() *2);
        target.draw(ammoText);
    }
}

void Game::drawUI(sf::RenderTarget &target){
    drawWeapon(target);
    drawHealth(target);
    drawAmmo(target);
}

void Game::handleDrawing(sf::RenderTarget &target){
    drawScene(target);
    drawSprites(target);
    drawUI(target);
}

void Game::updateEntities(sf::Time deltaT){
    for(auto i : entities){
        i->onApproach(player);
    }
    for(auto i : entities){
        i->onUpdate(deltaT, worldMap);
    }
    bool deletedSth = 1;
    while(deletedSth){
        deletedSth = 0;
        for(int i = 0; i < entities.size(); ++i){
            if (entities[i]->canBeDeleted()){
                entities.erase(entities.begin() + i);
                deletedSth = 1;
                break;
            }
        }
    }
}
void Game::updateEnemies(sf::Time deltaT){
    for(int i = 0; i < enemies.size(); i++){
        std::vector <std::shared_ptr<Enemy>> enemies_without_i = enemies;
        enemies_without_i.erase(enemies_without_i.begin() + i);
        enemies[i]->handleLogic(deltaT, player, worldMap, enemies_without_i, entities);
    }
}
void Game::onUpdate(sf::Time deltaT){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            player->forward(deltaT, worldMap, entities);
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            player->backward(deltaT, worldMap, entities);
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            player->rotateRight(deltaT, worldMap);
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            player->rotateLeft(deltaT, worldMap);
        }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
        player->handleWeaponSwap(FIST);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
        player->handleWeaponSwap(PISTOL);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
        player->handleWeaponSwap(SHOTGUN);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        player->performShoot(worldMap, enemies);
    }
    //handlePlayerEntitiesApproach();
    updateEntities(deltaT);
    updateEnemies(deltaT);
}


int Game::checkGameState(){
    if(checkIfAllEnemiesAreDead() == true) return WON;
    else if(player->getCurrentHp() < 0) return LOST;
    else return IN_GAME;
}
Game::~Game(){
    delete player;
    player = nullptr;
    delete worldMap;
    worldMap = nullptr;
    delete resManager;
    resManager = nullptr;
    entities.clear();
    enemies.clear();
}
