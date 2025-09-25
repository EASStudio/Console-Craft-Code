#pragma once
#ifndef MOB_INIT_H
#define MOB_INIT_H

#include "Map.h"

std::unique_ptr<MinableItems> createMinableItem(MapType mapType, char tileType);
std::unique_ptr<Mob> createEnemy(MapType mapType, char tileType);

#endif // !MOB_INIT_H