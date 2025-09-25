#include "Mob_Init.h"

// Clear console screen
void clearScreen()
{
#ifdef _WIN32
    system("cls");    // Windows Support
#else
    system("clear");  // Mac and Linux support
#endif
}

MapType currentMap = MapType::SPAWN_MAP;
std::vector<std::vector<char>> map(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, '.'));

const std::vector<std::vector<char>> spawnMap = {
    {'.','.','.','T','T','T','.','.','.','R','R','.','S','W','W'},
    {'L','.','.','T','T','T','.','.','.','R','R','.','S','W','W'},
    {'.','.','.','T','T','T','.','.','.','R','R','.','S','W','W'},
    {'.','.','.','T','T','T','.','.','.','R','R','.','S','W','W'},
    {'Z','.','.','T','T','T','.','.','.','R','R','L','S','W','W'},
    {'.','.','.','T','T','T','.','.','.','R','R','R','S','W','W'},
    {'.','Z','.','T','T','T','.','.','.','R','R','R','S','W','W'},
    {'.','.','.','T','T','T','.','.','.','R','>','R','S','W','W'},
    {'.','.','.','.','T','T','.','.','.','R','R','R','S','W','W'},
    {'.','.','.','.','L','.','.','.','.','R','R','R','S','W','W'},
    {'.','.','L','.','.','.','.','.','.','R','R','.','S','W','W'},
    {'.','.','.','.','.','.','.','.','.','R','R','.','S','W','W'},
    {'.','T','.','.','<','.','R','R','.','R','R','.','S','W','W'},
    {'T','T','Z','.','.','R','R','.','.','R','R','.','S','W','W'},
    {'T','T','.','.','Z','R','R','.','.','R','R','L','S','W','W'},
};

const std::vector<std::vector<char>> caveMap = {
    {'.','.','.','C','C','C','.','.','.','R','R','R','.','.','.'},
    {'L','.','.','R','C','R','.','L','.','R','I','R','.','.','.'},
    {'.','.','Z','R','R','R','.','.','.','I','I','.','Z','.','.'},
    {'.','.','.','R','I','R','.','.','.','C','R','.','.','C','C'},
    {'.','.','R','R','I','C','.','.','.','C','C','E','.','I','R'},
    {'.','.','R','R','I','R','Z','.','.','C','C','.','L','R','R'},
    {'L','.','C','R','I','C','.','.','.','.','.','.','R','W','R'},
    {'.','.','C','C','C','C','.','.','.','.','>','Z','I','I','R'},
    {'.','.','.','.','R','C','.','.','.','.','.','.','I','I','R'},
    {'.','.','.','Z','.','.','.','L','.','.','R','.','I','I','I'},
    {'.','Z','.','.','.','.','.','.','.','R','R','.','R','R','I'},
    {'.','.','.','.','E','.','.','.','.','I','I','.','R','R','R'},
    {'C','R','.','.','.','.','C','R','.','I','I','L','R','I','I'},
    {'R','R','.','L','.','R','C','R','R','I','R','.','R','R','R'},
    {'R','R','.','.','Z','R','R','C','C','I','R','R','R','R','R'},
};

const std::vector<std::vector<char>> bossCaveMap = {
    {'R','.','.','R','R','R','.','L','.','R','R','R','.','.','R'},
    {'R','.','E','R','R','R','.','.','.','R','.','R','Z','R','.'},
    {'R','.','.','R','R','R','.','R','.','R','Z','.','.','.','R'},
    {'.','.','.','R','R','R','.','R','.','R','.','.','.','.','.'},
    {'L','.','R','R','R','R','R','.','.','R','R','R','.','R','.'},
    {'.','.','R','R','R','R','R','.','L','.','R','.','R','R','R'},
    {'.','.','R','R','R','R','.','.','.','.','.','.','R','R','R'},
    {'.','.','.','R','R','.','L','.','.','.','.','.','R','R','R'},
    {'E','.','.','.','.','.','.','.','.','.','.','Z','.','R','R'},
    {'.','.','.','.','.','.','E','.','.','.','R','.','.','.','S'},
    {'.','.','Z','.','.','.','.','.','.','R','R','.','.','R','R'},
    {'.','R','.','.','.','.','.','A','.','I','R','.','R','R','R'},
    {'L','R','L','.','<','.','R','R','C','R','R','E','R','R','R'},
    {'R','R','.','.','.','R','R','R','R','R','R','.','R','R','R'},
    {'R','R','.','L','.','R','R','R','R','R','R','R','R','R','R'},
};

int spawnEntranceX = 5;
int spawnEntranceY = 10;
int caveEntranceX = 10;
int caveEntranceY = 7;
int bossEntranceX = 4;
int bossEntranceY = 12;

// For saving map data

std::vector<std::vector<char>> spawnMapState = spawnMap;
std::vector<std::vector<char>> caveMapState = caveMap;
std::vector<std::vector<char>> bossMapState = bossCaveMap;

void displayMap(const Player& player)
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (y == player.getPlayerY() && x == player.getPlayerX())
                std::cout << '@' << " ";
            else
                std::cout << map[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void loadMapState(const std::vector<std::vector<char>>& mapState)
{
    map = mapState;
}

// For when player wins or loses and wantes to play again
void resetMaps()
{
    spawnMapState = spawnMap;
    caveMapState = caveMap;
    bossMapState = bossCaveMap;

    // reset entrances to defaults
    spawnEntranceX = 5;  spawnEntranceY = 10;
    caveEntranceX = 10; caveEntranceY = 7;
    bossEntranceX = 4;  bossEntranceY = 12;
}

void updatePlayerPosition(std::unique_ptr<Player>& player, int newX, int newY)
{
    player->setPlayerPosition(newX, newY);

    // Save last position per map
    switch (currentMap)
    {
    case MapType::SPAWN_MAP:
        spawnEntranceX = newX; spawnEntranceY = newY; break;

    case MapType::CAVE_MAP:
        caveEntranceX = newX;  caveEntranceY = newY;  break;

    case MapType::BOSS_CAVE_MAP:
        bossEntranceX = newX; bossEntranceY = newY; break;
    }
}

// Mining functions

bool mineTree(std::unique_ptr<Player>& player, Items* item, int x, int y)
{
    auto mineItem = createMinableItem(currentMap, 'T');
    std::cout << "Enter X to chop.\n";

    while (player->isAlive() && mineItem->isAlive())
    {
        char mine;
        std::cin >> mine;
        mine = static_cast<char>(tolower(mine));

        if (mine == 'x')
        {
            int totalDamage = player->getMiningPower();
            mineItem->takeDamage(totalDamage);

            if (!mineItem->isAlive())
            {
                clearScreen();
                std::cout << "You mined a Tree.\n";
                player->useStamina(1);
                player->gainWood(4);
                player->gainApples(1);
                player->gainAcorns(1);
                player->gainScore(25);

                updateMapState(x, y, '.');
                return true;
            }
        }
        else std::cout << "Invalid action.\n";
    }
    return false;
}

bool mineRock(std::unique_ptr<Player>& player, Items* item, int x, int y)
{
    auto mineItem = createMinableItem(currentMap, 'R');
    std::cout << "Enter X to mine.\n";

    while (player->isAlive() && mineItem->isAlive())
    {
        char mine;
        std::cin >> mine;
        mine = static_cast<char>(tolower(mine));

        if (mine == 'x')
        {
            int totalDamage = player->getMiningPower();
            mineItem->takeDamage(totalDamage);

            if (!mineItem->isAlive())
            {
                clearScreen();
                std::cout << "You mined a Rock.\n";
                player->useStamina(2);
                player->gainRock(5);
                player->gainCoal(1);
                player->gainScore(25);

                updateMapState(x, y, '.');
                return true;
            }
        }
        else std::cout << "Invalid action.\n";
    }
    return false;
}

bool mineCoal(std::unique_ptr<Player>& player, Items* item, int x, int y)
{
    auto mineItem = createMinableItem(currentMap, 'C');
    std::cout << "Enter X to mine.\n";

    while (player->isAlive() && mineItem->isAlive())
    {
        char mine;
        std::cin >> mine;
        mine = static_cast<char>(tolower(mine));

        if (mine == 'x')
        {
            int totalDamage = player->getMiningPower();
            mineItem->takeDamage(totalDamage);

            if (!mineItem->isAlive())
            {
                clearScreen();
                std::cout << "You mined Coal.\n";
                player->useStamina(3);
                player->gainCoal(8);
                player->gainScore(30);

                updateMapState(x, y, '.');
                return true;
            }
        }
        else std::cout << "Invalid action.\n";
    }
    return false;
}

bool mineIron(std::unique_ptr<Player>& player, Items* item, int x, int y)
{
    auto mineItem = createMinableItem(currentMap, 'I');
    std::cout << "Enter X to mine.\n";

    while (player->isAlive() && mineItem->isAlive())
    {
        char mine;
        std::cin >> mine;
        mine = static_cast<char>(tolower(mine));

        if (mine == 'x')
        { 
            int totalDamage = player->getMiningPower();
            mineItem->takeDamage(totalDamage);

            if (!mineItem->isAlive())
            {
                clearScreen();
                std::cout << "You mined Iron.\n";
                player->useStamina(3);
                player->gainIronOre(4);
                player->gainScore(80);

                updateMapState(x, y, '.');
                return true;
            }
        }
        else std::cout << "Invalid action.\n";
    }
    return false;
}

bool combat(std::unique_ptr<Player>& player, Items* item, int x, int y, char enemyTile)
{
    auto enemy = createEnemy(currentMap, enemyTile);
    std::cout << "Enter X to attack.\n";

    while (player->isAlive() && enemy->isAlive())
    {
        char attack;
        std::cin >> attack;
        attack = static_cast<char>(tolower(attack));

        if (attack == 'x')
        {
            int totalDamage = player->getPlayerAttack();
            enemy->takeDamage(totalDamage);

            if (!enemy->isAlive())
            {
                clearScreen();
                std::cout << "You defeated the enemy!\n";
                player->useStamina(2);
                player->gainScore(50);
                updateMapState(x, y, '.');
                return true;
            }
        }
        else std::cout << "Invalid action.\n";

        if (enemy->isAlive())
            player->takeDamage(enemy->getMobAttack());
    }

    if (!player->isAlive())
        clearScreen();
        std::cout << "You have died in battle.\n";

    return false;
}

bool bossCombat(std::unique_ptr<Player>& player, Items* item, int x, int y, char enemyTile)
{
    auto enemy = createEnemy(currentMap, enemyTile);
    std::cout << "Enter X to attack.\n";

    while (player->isAlive() && enemy->isAlive())
    {
        char attack;
        std::cin >> attack;
        attack = static_cast<char>(tolower(attack));

        if (attack == 'x')
        {
            int totalDamage = player->getPlayerAttack();
            enemy->takeDamage(totalDamage);

            if (!enemy->isAlive())
            {
                clearScreen();
                std::cout << "You defeated the Air Wizard!\n";
                std::cout << "You beat the game!\n";
                player->gainScore(50);
                std::cout << "Final Score: " << player->displayScore() << "\n";
                exit(0);
            }
        }
        else std::cout << "Invalid action.\n";

        if (enemy->isAlive())
            player->takeDamage(enemy->getMobAttack());
    }

    if (!player->isAlive())
        clearScreen();
        std::cout << "You have died fighting the Air Wizard.\n";

    return false;
}

// Map updating functions

void movePlayer(char dir, std::unique_ptr<Player>& player, Items* item)
{
    int newX = player->getPlayerX();
    int newY = player->getPlayerY();

    if (dir == 'w') newY--;
    else if (dir == 's') newY++;
    else if (dir == 'a') newX--;
    else if (dir == 'd') newX++;
    else return;

    if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT)
    {
        std::cout << "You can't move outside the map!\n";
        return;
    }

    char dest = map[newY][newX];

    switch (dest)
    {
    case '.': case 'S': case 'W':
        updatePlayerPosition(player, newX, newY); break;

    case 'R':
        if (player->getPlayerStamina() < 2) 
        {
            std::cout << "You are to tired to mine the rock!\n";
            std::cout << "Try x/rest to rest and recover some stamina!\n";
            return;
        }

        else
        {
            mineRock(player, item, newX, newY);
            updatePlayerPosition(player, newX, newY);
            break;
        }

    case 'T':
        if (player->getPlayerStamina() < 1) 
        {
            std::cout << "You are to tired to chop the tree!\n";
            std::cout << "Try x/rest to rest and recover some stamina!\n";
            return;
        }

        else 
        {
            mineTree(player, item, newX, newY);
            updatePlayerPosition(player, newX, newY);
            break;
        }

    case 'C':
        if (player->getPlayerStamina() < 3)
        {
            std::cout << "You are to tired to mine the coal!\n";
            std::cout << "Try x/rest to rest and recover some stamina!\n";
            return;
        }

        else
        {
            mineCoal(player, item, newX, newY);
            updatePlayerPosition(player, newX, newY);
            break;
        }

    case 'I':
        if (player->getPlayerStamina() < 3) 
        {
            std::cout << "You are to tired to mine the iron!\n";
            std::cout << "Try x/rest to rest and recover some stamina!\n";
            return;
        }

        else
        {
            mineIron(player, item, newX, newY);
            updatePlayerPosition(player, newX, newY);
            break;
        }

    case 'Z': case 'L': case 'E':
        if (player->getPlayerStamina() < 2) 
        {
            std::cout << "You are to tired to fight!\n";
            std::cout << "Try x/rest to rest and recover some stamina!\n";
            player->takeDamage(3);
            return;
        }

        else
        {
            combat(player, item, newX, newY, dest);
            updatePlayerPosition(player, newX, newY);
            break;
        }

    case 'A':
        if (player->getPlayerStamina() < 4) 
        {
            std::cout << "You are to tired to fight the Air Wizard!\n";
            std::cout << "Try x/rest to rest and recover some stamina!\n";
            player->takeDamage(5);
            return;
        }
        bossCombat(player, item, newX, newY, dest);
        updatePlayerPosition(player, newX, newY);
        break;

    case '>': case '<':
        loadNextMap(*player, dest);
        break;

    default: std::cout << "You can't move there!\n";
        break;
    }
}

void updateMapState(int x, int y, char newTile)
{
    map[y][x] = newTile;

    switch (currentMap)
    {
    case MapType::SPAWN_MAP: 
        spawnMapState[y][x] = newTile; 
        break;

    case MapType::CAVE_MAP: 
        caveMapState[y][x] = newTile; 
        break;

    case MapType::BOSS_CAVE_MAP: 
        bossMapState[y][x] = newTile; 
        break;
    }
}

void loadNextMap(Player& player, char dest)
{
    switch (currentMap)
    {
    case MapType::SPAWN_MAP:
        if (dest == '>') 
        { 
            currentMap = MapType::CAVE_MAP;  
            loadMapState(caveMapState); 
            player.setPlayerPosition(caveEntranceX, caveEntranceY); 
        }

        else if (dest == '<') 
        { 
            currentMap = MapType::BOSS_CAVE_MAP; 
            loadMapState(bossMapState);
            player.setPlayerPosition(bossEntranceX, bossEntranceY);
        }
        break;

    case MapType::CAVE_MAP:
        if (dest == '>') 
        {
            currentMap = MapType::SPAWN_MAP;
            loadMapState(spawnMapState);
            player.setPlayerPosition(spawnEntranceX, spawnEntranceY); 
        }
        break;

    case MapType::BOSS_CAVE_MAP:
        if (dest == '<') 
        {
            currentMap = MapType::SPAWN_MAP;
            loadMapState(spawnMapState);
            player.setPlayerPosition(spawnEntranceX, spawnEntranceY); 
        }
        break;
    }
}