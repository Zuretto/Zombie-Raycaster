cmake_minimum_required(VERSION "3.19.2")


project(Zombie_Raycaster VERSION 1.0.0)

#add_compile_options(-IC:/SFML/include -LC:/SFML/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system)
#add_definitions(-IC:/SFML/include -LC:/SFML/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system)

#set (CMAKE_CXX_FLAGS -IC:/SFML/include -LC:/SFML/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system)
add_executable(Zombie_Raycaster main.cpp Player.cpp Map.cpp Game.cpp Entity.cpp Weapon.cpp Enemy.cpp Menu.cpp Resource_Manager.cpp)
target_link_libraries(Zombie_Raycaster PRIVATE sfml-window sfml-audio sfml-graphics sfml-network sfml-system)
