#pragma once
#define M_PI 3.14159265358979323846
#define weapon_states 2
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

enum gun_enum {WEAPON, FIST, PISTOL, SHOTGUN, GUN_TYPES_NUMBER};

enum gun_states {DRAWN, SHOOT, WEAPON_STATES_NUMBER};

enum enemy_states {ALIVE, DIED1, DIED2, DEAD, ENEMY_STATES_NUMBER};

enum enemy_num {ENEMY, ZOMBIE, SKELETON, ENEMY_TYPES_NUMBER};

enum entity_enum {ENTITY, BARREL, TABLE, LAMP, PILLAR, ENTITY_TYPES_NUMBER};