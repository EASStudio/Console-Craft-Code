#include "Mob_Init.h"

std::unique_ptr<MinableItems> createMinableItem(MapType mapType, char tileType)
{
    switch (tileType)
    {
    case 'T': 
        return std::make_unique<Tree>();

    case 'R': 
        return std::make_unique<Rock>();

    case 'C': 
        return std::make_unique<Coal>();

    case 'I': 
        return std::make_unique<Iron>();

    default:  
        return std::make_unique<Rock>(); 
    }
}

std::unique_ptr<Mob> createEnemy(MapType mapType, char tileType)
{
    switch (tileType)
    {
    case 'Z': 
        return std::make_unique<Zombie>();

    case 'L':
        return std::make_unique<Slime>();

    case 'E':
        return std::make_unique<Creeper>();

    case 'A':
        return std::make_unique<AirWizard>();

    default:
        return std::make_unique<Slime>(); 
    }
}

