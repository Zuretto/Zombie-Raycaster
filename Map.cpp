#include "Map.hpp"
int Map::width() const{
    return map_vector[0].size();
}
int Map::height() const{
    return map_vector.size();
}
int Map::pixelWidth() const{
    return this->initWidth;
}
int Map::pixelHeight() const{
    return this->initHeight;
}
std::vector <std::vector <int>> Map::getMapVector() const{
    std::vector <std::vector <int>> map_vector2 = map_vector;
    return map_vector2;
}
Map::Map(std::string fileName, int width, int height){
    initWidth = width;
    initHeight = height;
    std::ifstream fp(fileName);
    if(!fp){
        std::cerr << "Failed to load map file " << fileName;
    }
    std::string str;
    while (std::getline(fp, str)){
        std::stringstream sstream(str);
        std::vector<int> temp_vector;
        int temp_int;
        while (sstream >> temp_int){
            temp_vector.push_back(temp_int);
        }
        map_vector.push_back(temp_vector);
        if (fp.eof()) break;
    }
}
Map::~Map(){
    std::cout << "hej" << std::endl;
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    //std::vector <std::vector <int>> map_vector;
    for(int row = 0; row < this->width(); row++){
        for(int col = 0; col < this->height(); col++){
            double squareX = (double)initWidth/this->width();
            double squareY = (double)initHeight/this->height();
            sf::RectangleShape rectangle(sf::Vector2f(squareX, squareY));
            rectangle.setPosition(col*squareX, row*squareY);
            if (map_vector[row][col] == 0) rectangle.setFillColor(sf::Color::Black);
            else if (map_vector[row][col] == 1) rectangle.setFillColor(sf::Color(5, 54, 168));
            else if (map_vector[row][col] == 2) rectangle.setFillColor(sf::Color(163, 5, 23));
            else if (map_vector[row][col] == 3) rectangle.setFillColor(sf::Color(107, 104, 9));
            else if (map_vector[row][col] == 4) rectangle.setFillColor(sf::Color(17, 105, 31));
            else if (map_vector[row][col] == 5) rectangle.setFillColor(sf::Color(156, 19, 146));
            target.draw(rectangle);
        }
    }
}

/*
void Map::draw(sf::RenderTarget &target, int width, int height){
    //std::vector <std::vector <int>> map_vector;
    for(int row = 0; row < this->width(); row++){
        for(int col = 0; col < this->height(); col++){
            double squareX = (double)width/this->width();
            double squareY = (double)height/this->height();
            sf::RectangleShape rectangle(sf::Vector2f(squareX, squareY));
            rectangle.setPosition(col*squareX, row*squareY);
            if (map_vector[row][col] == 0) rectangle.setFillColor(sf::Color::Black);
            else if (map_vector[row][col] == 1) rectangle.setFillColor(sf::Color(5, 54, 168));
            else if (map_vector[row][col] == 2) rectangle.setFillColor(sf::Color(163, 5, 23));
            else if (map_vector[row][col] == 3) rectangle.setFillColor(sf::Color(107, 104, 9));
            else if (map_vector[row][col] == 4) rectangle.setFillColor(sf::Color(17, 105, 31));
            else if (map_vector[row][col] == 5) rectangle.setFillColor(sf::Color(156, 19, 146));
            target.draw(rectangle);
        }
    }
}
*/