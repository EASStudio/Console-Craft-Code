#include "Map.h"
#include "Game.h"
#include <thread>
#include <string>

// Wait for an amount of time
void wait(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

Game::Game() 
{ 
    isRunning = false;
}

Game::~Game() 
{

}

void Game::Run()
{
    isRunning = true;
    Init();
}

void Game::Shutdown()
{
    isRunning = false;
    exit(0);
}

void Game::Init()
{
    bool inMenu = true;

    while (inMenu)
    {
        std::cout << " Console Craft\n";
        std::cout << " <[S]tart Game>\n";
        std::cout << "<[H]ow To Play>\n";
        std::cout << "  <[A]bout>\n";
        std::cout << "  <[Q]uit>\n>";

        std::string s_input;
        std::cin >> s_input;
        std::transform(s_input.begin(), s_input.end(), s_input.begin(), ::tolower);

        if (s_input == "h")
        {
            std::cout << "             --- How To Play ---\n";
            std::cout << "WASD to move. E to open Inventory.\n";
            std::cout << "C to craft. X/item to use an item.\n";
            std::cout << "X/rest to rest and gain gain some stamina.\n";
            std::cout << "Z to equip items. Beat the Air Wizard to win.\n";
            std::cout << "Press enter to continue.\n>";
            std::string key; 
            std::getline(std::cin, key);
            std::cin.get(); 
            clearScreen();
        }

        else if (s_input == "a")
        {
            std::cout << "                   --- About ---\n";
            std::cout << "Console Craft is inspired by Minicraft by Notch.\n";
            std::cout << "Created to provide a similar adventure experience.\n";
            std::cout << "Press enter to continue.\n>";
            std::string key;
            std::getline(std::cin, key);
            std::cin.get();
            clearScreen();
        }

        else if (s_input == "q")
        {
            Shutdown();
        }

        else if (s_input == "s")
        {
            clearScreen();

            // Display map identitys

            std::cout << "You must defeat the Air Wizard!\n";
            std::cout << "Here are all the enemys on your jounery!\n";
            std::cout << "Z = Zombie\n";
            std::cout << "L = Slime\n";
            std::cout << "E = Creeper\n";
            std::cout << "A = Air Wizard\n";
            std::cout << "Note: The slimes get stronger around the Air Wizard!\n";
            std::cout << "\n";

            wait(3);
            clearScreen();
            resetMaps();

            auto player = std::make_unique<Player>();
            auto item = std::make_unique<PowGlove>();

            currentMap = MapType::SPAWN_MAP;
            loadMapState(spawnMapState);
            updatePlayerPosition(player, spawnEntranceX, spawnEntranceY);

            bool running = true;

            while (running && player->isAlive())
            {
                displayMap(*player);
                player->displayStats();
                item->displayItems();

                std::string p_input;
                std::cin >> p_input;
                std::transform(p_input.begin(), p_input.end(), p_input.begin(), ::tolower);
                clearScreen();

                if (p_input == "e")
                {
                    bool inInventory = true;

                    while (inInventory)
                    {
                        clearScreen();
                        player->displayInventory();
                        std::cout << "Press Q to exit.\n> ";

                        std::string inv_input;
                        std::getline(std::cin, inv_input);
                        std::transform(inv_input.begin(), inv_input.end(), inv_input.begin(), ::tolower);

                        if (inv_input == "q")
                        {
                            inInventory = false;
                            clearScreen();
                        }

                        else
                        {
                            std::cout << "Invalid input. Press enter to continue.\n";
                            std::cin.get();
                        }
                    }
                }

                else if (p_input == "c")
                {
                    bool inCrafting = true;

                    while (inCrafting)
                    {
                        clearScreen();
                        player->displayCraftingMenu();
                        std::cout << "Type item to craft or Q to exit.\n> ";

                        std::string c_input;
                        std::getline(std::cin, c_input);
                        std::transform(c_input.begin(), c_input.end(), c_input.begin(), ::tolower);

                        if (c_input == "q")
                        {
                            inCrafting = false;
                            clearScreen();
                        }

                        else if (!c_input.empty())
                        {
                            player->craftItem(c_input);
                            player->displayCraftedItems();
                            std::cout << "Press enter to continue.\n";
                            std::cin.get();
                        }
                    }
                }

                else if (p_input == "z")
                {
                    bool inEquip = true;

                    while (inEquip)
                    {
                        clearScreen();
                        player->displayInventory();
                        std::cout << "\nEnter tool or armor, or Q to exit.\n> ";

                        std::string e_input;
                        std::getline(std::cin, e_input);
                        std::transform(e_input.begin(), e_input.end(), e_input.begin(), ::tolower);

                        if (e_input == "q")
                        {
                            inEquip = false;
                            clearScreen();
                        }

                        else if (e_input == "tool")
                        {
                            std::cout << "Enter what tool you want to equip or press enter to continue.\n> ";
                            std::string t_input;
                            std::getline(std::cin, t_input);
                            std::transform(t_input.begin(), t_input.end(), t_input.begin(), ::tolower);

                            if (!t_input.empty())
                                player->equipItem(t_input);

                            std::cout << "Press enter to continue.\n";
                            std::cin.get();
                        }

                        else if (e_input == "armor")
                        {
                            std::cout << "Enter what armor you want to equip or press enter to continue.\n> ";
                            std::string a_input;
                            std::getline(std::cin, a_input);
                            std::transform(a_input.begin(), a_input.end(), a_input.begin(), ::tolower);

                            if (!a_input.empty())
                                player->equipArmor(a_input);

                            std::cout << "Press enter to continue.\n";
                            std::cin.get();
                        }

                        else
                        {
                            std::cout << "Invalid input. Press enter to try again.\n";
                            std::cin.get();
                        }
                    }
                }


                else if (p_input == "x/apple") 
                {
                    player->eatApple();
                }

                else if (p_input == "x/rest") 
                {
                    player->rest();
                }

                else if (p_input == "x/bench")
                {
                    bool inBench = true;

                    while (inBench)
                    {
                        clearScreen();
                        player->displayCraftingBenchMenu();
                        std::cout << "Type item to craft or Q to exit.\n> ";

                        std::string b_input;
                        std::getline(std::cin, b_input);
                        std::transform(b_input.begin(), b_input.end(), b_input.begin(), ::tolower);

                        if (b_input == "q")
                        {
                            inBench = false;
                            clearScreen();
                        }

                        else if (!b_input.empty())
                        {
                            player->craftItem(b_input);
                            player->displayCraftedItems();
                            std::cout << "Press enter to continue.\n";
                            std::cin.get();
                        }
                    }
                    }

                else if (p_input == "x/anvil")
                {
                    bool inAnvil = true;

                    while (inAnvil)
                    {
                        clearScreen();
                        player->displayAnvilMenu();
                        std::cout << "Type item to forge or Q to exit.\n> ";

                        std::string a_input;
                        std::getline(std::cin, a_input);
                        std::transform(a_input.begin(), a_input.end(), a_input.begin(), ::tolower);

                        if (a_input == "q")
                        {
                            inAnvil = false;
                            clearScreen();
                        }

                        else if (!a_input.empty())
                        {
                            player->craftArmor(a_input);
                            player->displayCraftedArmor();
                            std::cout << "Press enter to continue.\n";
                            std::cin.get();
                        }
                    }
                    }

                else if (p_input == "x/furnace") 
                {
                    bool inFurnace = true;

                    while (inFurnace)
                    {
                        clearScreen();
                        player->displayFurnaceMenu();
                        std::cout << "Type Iron to smelt, or Q to exit.\n> ";

                        std::string f_input;
                        std::getline(std::cin, f_input);
                        std::transform(f_input.begin(), f_input.end(), f_input.begin(), ::tolower);

                        if (f_input == "q") 
                        {
                            inFurnace = false;
                            clearScreen();
                        }

                        else if (f_input == "iron") 
                        {
                            player->getIronOre();
                            player->getCoal();
                            std::cout << "How many iron do you want to smelt? (1-100)\n> ";
                            std::string amountStr;
                            std::getline(std::cin, amountStr);

                            int amount = 0;

                            try 
                            {
                                amount = std::stoi(amountStr);
                            }

                            catch (...) 
                            {
                                std::cout << "Invalid number. Press enter to continue.\n";
                                std::cin.get();
                                continue;
                            }

                            player->useFurnace("iron", amount);
                            std::cout << "Press enter to continue.\n";
                            std::cin.get();
                        }

                        else 
                        {
                            std::cout << "Invalid input. Only 'iron' or 'q' are allowed.\n";
                            std::cout << "Press enter to continue...\n";
                            std::cin.get();
                        }
                    }
                    }

                else if (p_input == "x")
                {
                    std::cout << "Use x/item format like x/apple or x/bench.\n";
                }

                else if (p_input.size() == 1) 
                {
                    movePlayer(p_input[0], player, item.get());
                }

                else 
                {
                    std::cout << "Invalid Input\n";
                }
            }

            if (!player->isAlive())
            {
                std::cout << "Score: " << player->displayScore() << "\n";
                std::cout << "Press enter to return to the menu.\n>";
                std::string key; 
                std::getline(std::cin, key);
                std::cin.get();
                clearScreen();
            }
        }
        else std::cout << "Invalid Input\n";
        clearScreen();
    }
}
