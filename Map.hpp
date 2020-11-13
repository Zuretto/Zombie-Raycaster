#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
class Map : public sf::Drawable{
private:
    std::vector <std::vector <int>> map_vector;
    int initWidth;
    int initHeight;
public:
    int width() const;
    int height() const;
    int pixelWidth() const;
    int pixelHeight() const;
    std::vector <std::vector <int>> getMapVector() const;
    Map(std::string fileName, int width, int height);
    ~Map();
    //void draw(sf::RenderTarget &target, int width, int height);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};