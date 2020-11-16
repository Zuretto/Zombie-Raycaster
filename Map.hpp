#pragma once
#include "definitions.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

class Map{
private:
    std::vector <std::vector <int>> map_vector;
public:
    int width() const;
    int height() const;
    std::vector <std::vector <int>> getMapVector() const;
    Map(std::string fileName);
    ~Map();
};