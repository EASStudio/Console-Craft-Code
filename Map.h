#pragma once
#ifndef MAP_H
#define MAP_H

#include "Entity.h"

// Map size
constexpr int MAP_HEIGHT = 15;
constexpr int MAP_WIDTH = 15;

// Map types
enum class MapType
{
    SPAWN_MAP,
    CAVE_MAP,
    BOSS_CAVE_MAP
};

// Current map type
extern MapType currentMap;

// Current visible map
extern std::vector<std::vector<char>> map;

// State of a map  
extern std::vector<std::vector<char>> spawnMapState;
extern std::vector<std::vector<char>> caveMapState;
extern std::vector<std::vector<char>> bossCaveMapState;

// Predefined maps
extern const std::vector<std::vector<char>> spawnMap;
extern const std::vector<std::vector<char>> caveMap;
extern const std::vector<std::vector<char>> bossCaveMap;

// Player entrance positions
extern int spawnEntranceX;
extern int spawnEntranceY;
extern int caveEntranceX;
extern int caveEntranceY;
extern int bossEntranceX;
extern int bossEntranceY;

// Map functions
void clearScreen();
void loadMapState(const std::vector<std::vector<char>>& stateMap);
void resetMaps();
void displayMap(const class Player& player);
void loadNextMap(class Player& player, char dest);
void updateMapState(int x, int y, char newTile = '.');
void updatePlayerPosition(std::unique_ptr<Player>& player, int newX, int newY);
void movePlayer(char dir, std::unique_ptr<Player>& player, Items* item);
bool mineTree(std::unique_ptr<Player>& player, Items* item, int x, int y);
bool mineRock(std::unique_ptr<Player>& player, Items* item, int x, int y);
bool mineCoal(std::unique_ptr<Player>& player, Items* item, int x, int y);
bool mineIron(std::unique_ptr<Player>& player, Items* item, int x, int y);
bool combat(std::unique_ptr<Player>& player, Items* item, int x, int y, char enemyTile);
bool bossCombat(std::unique_ptr<Player>& player, Items* item, int x, int y, char enemyTile);

#endif // MAP_H
