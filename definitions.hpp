#pragma once
#define M_PI 3.14159265358979323846
#define casterWidth 1024
#define casterHeight 720
#define texWidth 32
#define texHeight 32
#define entityWidth 64
#define entityHeight 64
#define enemyWidth 64
#define enemyHeight 64
#define weaponWidth 128
#define weaponHeight 128
#define enemyAttackRange 1

enum game_states {IN_MENU, IN_OPTIONS, IN_GAME, WON, LOST, GAME_STATES_NUMBER};

enum weapon_enum {WEAPON, FIST, PISTOL, SHOTGUN, WEAPON_TYPES_NUMBER};

enum weapon_states {DRAWN, SHOT1, SHOT2, SHOT3, WEAPON_STATES_NUMBER};

enum enemy_states {ALIVE, DIED1, DIED2, DEAD, ENEMY_STATES_NUMBER};

enum enemy_num {ENEMY, ZOMBIE, SKELETON, FIRE_WIZARD, ENEMY_TYPES_NUMBER};

enum entity_enum {ENTITY, BARREL, PILLAR, AMMO_PISTOL, AMMO_SHOTGUN, HAMBURGER, SODA, FIREBALL, ENTITY_TYPES_NUMBER};



