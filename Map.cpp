#include "Map.hpp"
int Map::width() const{
    return map_vector[0].size();
}
int Map::height() const{
    return map_vector.size();
}
std::vector <std::vector <int>> Map::getMapVector() const{
    std::vector <std::vector <int>> map_vector2 = map_vector;
    return map_vector2;
}
Map::Map(std::string fileName){
    std::ifstream fp(fileName);
    if(!fp){
        std::cerr << "Failed to load map file " << fileName;
    }
    std::string str;
    while (std::getline(fp, str) && str != "OBJECTS_LOADING:"){
        std::stringstream sstream(str);
        std::vector<int> temp_vector;
        int temp_int;
        while (sstream >> temp_int){
            temp_vector.push_back(temp_int);
        }
        map_vector.push_back(temp_vector);
        if (fp.eof()) break;
    }
    fp.close();
}
Map::~Map(){
    //std::cout << "deleted Map" << std::endl;
    this->map_vector.clear();
}