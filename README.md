# Zombie-Raycaster
The goal of the project was to develop a simple first-person-shooter game using Ray Tracing technology. The game has few features, like:
- reading map from the file
- reading player and objects positions from the file
- 3 types of weapons, featuring shotgun that shots bullets in a cone
- 3 types of enemies, featuring wizard that shots fireballs that can be seen and walked into
- bunch of entities that can be interacted with, like hamburgers that heal the player when walked into or barells that are tossed by the player

# Compilation 
to compile the project I was using Windows 10's command prompt with MinGW compiler installed. The command is:
  C:\MinGW\bin\g++.exe -g main.cpp Player.cpp Map.cpp Game.cpp Entity.cpp Weapon.cpp Enemy.cpp Menu.cpp Resource_Manager.cpp -o main.exe -IC:\SFML\include -LC:\SFML\lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
Where in the -I and -L flags, on your computer you should put a path to SFML\include directory and SFML\lib directory.
I also prepared a Cmake file, but I'm not sure if it will work on someone else's machine.
