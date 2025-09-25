#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <algorithm>
#include <memory>
#include <vector>
#include "Items.h"

// Player

class Player 
{
public: 
	Player()
		: m_pHealth(10),
		m_pMaxHealth(10),
		m_pStamina(10),
		m_pMaxStamina(10),
		m_pAttack(1),
		m_pPosX(0),
		m_pPosY(0),
		m_pScore(0),
		m_pWood(0),
		m_pApples(0),
		m_pAcorns(0),
		m_pSlimeBalls(0),
		m_pRock(0),
		m_pCoal(0),
		m_pIronOre(0),
		m_pIron(0),
		equippedItem(nullptr),
		equippedArmor(nullptr)
	{

	}

	// Game Menus

	void displayStats() const 
	{
		std::cout << "Health: " << m_pHealth << "/" << m_pMaxHealth << "\n";
		std::cout << "Stamina: " << m_pStamina << "/" << m_pMaxStamina << "\n";

		if (equippedItem) 
		{
			std::cout << "Equipped: " << equippedItem->displayItems() << "\n";
		}

		if (equippedArmor)
		{
			std::cout << "Armor: " << equippedArmor->displayItems() << "\n";
		}
	}

	int displayScore() const
	{
		return m_pScore;
	}

	void displayInventory() const 
	{
		std::cout << "          ---Inventory---           \n";
		std::cout << "Pow Glove\n";
		std::cout << "Slime balls: " << m_pSlimeBalls << "\n";
		std::cout << "Wood: " << m_pWood << "\n";
		std::cout << "Acorns: " << m_pAcorns << "\n";
		std::cout << "Apples: " << m_pApples << "\n";
		std::cout << "Rocks: " << m_pRock << "\n";
		std::cout << "Coal: " << m_pCoal << "\n";
		std::cout << "Iron Ore: " << m_pIronOre << "\n";
		std::cout << "Iron: " << m_pIron << "\n";
		displayCraftedItems();
		displayCraftedArmor();
	}

	void displayCraftedItems() const 
	{
		if (craftedItems.empty()) 
		{
			std::cout << "No items crafted.\n";
		}
		else 
		{
			for (const auto& item : craftedItems) 
			{
				std::cout << "- " << item->displayItems() << "\n";
			}
		}
	}

	void displayCraftedArmor() const
	{
		if (craftedArmor.empty())
		{
			std::cout << "No armor crafted.\n";
		}
		else
		{
			for (const auto& item : craftedArmor)
			{
				std::cout << "- " << item->displayItems() << "\n";
			}
		}
	}

	void displayCraftingMenu() const 
	{
		std::cout << "     ---Crafting---     \n";
		std::cout << "Crafting Bench : 4 Wood\n";
		std::cout << "Goo : 1 Slime ball\n";
	}

	void displayCraftingBenchMenu() const
	{
		std::cout << "      ---Crafting Bench---      \n";
		std::cout << "Crafting Bench : 4 Wood\n";
		std::cout << "Goo            : 1 Slime ball\n";
		std::cout << "Anvil          : 8 Iron\n";
		std::cout << "Furnace        : 6 Rock\n";
		std::cout << "Wood Sword     : 4 Wood\n";
		std::cout << "Wood Pick      : 5 Wood\n";
		std::cout << "Wood Axe       : 5 Wood\n";
		std::cout << "Wood Shovel    : 3 Wood\n";
		std::cout << "Rock Sword     : 2 Wood + 2 Rock\n";
		std::cout << "Rock Pick      : 2 Wood + 3 Rock\n";
		std::cout << "Rock Axe       : 2 Wood + 3 Rock\n";
		std::cout << "Rock Shovel    : 2 Wood + 1 Rock\n";
	}

	void displayAnvilMenu() const
	{
		std::cout << "        ---Anvil---      \n";
		std::cout << "Iron Armor    : 24 Iron\n";
	}

	void displayFurnaceMenu() const
	{
		std::cout << "        ---Anvil---      \n";
		std::cout << "Iron    : 1 Iron Ore + 1 Coal\n";
	}

	// Crafting System

	void craftItem(const std::string& itemName) 
	{
		if (itemName == "crafting bench") 
		{
			if (m_pWood >= 4)
			{
				m_pWood -= 4;
				craftedItems.push_back(std::make_unique<CraftingBench>());
				std::cout << "Crafted a Crafting Bench\n";
			}
			else std::cout << "Not enough wood\n";
		}

		else if (itemName == "goo")
		{
			if (m_pSlimeBalls >= 1)
			{
				m_pSlimeBalls -= 1;
				craftedItems.push_back(std::make_unique<Goo>());
				std::cout << "Crafted some Goo\n";
			}
			else std::cout << "Not enough slime balls\n";
		}

		else if (itemName == "anvil")
		{
			if (m_pIron >= 8)
			{
				m_pIron -= 8;
				craftedItems.push_back(std::make_unique<Anvil>());
				std::cout << "Crafted a Anvil\n";
			}
			else std::cout << "Not enough iron\n";
		}

		else if (itemName == "furnace")
		{
			if (m_pRock >= 6)
			{
				m_pRock -= 6;
				craftedItems.push_back(std::make_unique<Furnace>());
				std::cout << "Crafted a Furnace\n";
			}
			else std::cout << "Not enough rock\n";
		}

		// Tools
		else if (itemName == "wood sword") 
		{
			if (m_pWood >= 4) 
			{
				m_pWood -= 4;
				craftedItems.push_back(std::make_unique<WoodSword>());
				std::cout << "Crafted a Wood Sword\n";
			}
			else std::cout << "Not enough wood\n";
		}

		else if (itemName == "wood pick") 
		{
			if (m_pWood >= 5) 
			{
				m_pWood -= 5;
				craftedItems.push_back(std::make_unique<WoodPick>());
				std::cout << "Crafted a Wood Pick\n";
			}
			else std::cout << "Not enough wood\n";
		}

		else if (itemName == "wood axe") 
		{
			if (m_pWood >= 5) 
			{
				m_pWood -= 5;
				craftedItems.push_back(std::make_unique<WoodAxe>());
				std::cout << "Crafted a Wood Axe\n";
			}
			else std::cout << "Not enough wood\n";
		}

		else if (itemName == "wood shovel")
		{
			if (m_pWood >= 3) 
			{
				m_pWood -= 3;
				craftedItems.push_back(std::make_unique<WoodShovel>());
				std::cout << "Crafted a Wood Shove\n";
			}
			else std::cout << "Not enough wood\n";
		}

		else if (itemName == "rock sword") 
		{
			if (m_pWood >= 2 && m_pRock >= 2) 
			{
				m_pWood -= 2; m_pRock -= 2;
				craftedItems.push_back(std::make_unique<RockSword>());
				std::cout << "Crafted a Rock Sword\n";
			}
			else std::cout << "Not enough resources\n";
		}

		else if (itemName == "rock pick") 
		{
			if (m_pWood >= 2 && m_pRock >= 3) 
			{
				m_pWood -= 2; m_pRock -= 3;
				craftedItems.push_back(std::make_unique<RockPick>());
				std::cout << "Crafted a Rock Pick\n";
			}
			else std::cout << "Not enough resources\n";
		}

		else if (itemName == "rock axe") 
		{
			if (m_pWood >= 2 && m_pRock >= 3) 
			{
				m_pWood -= 2; m_pRock -= 3;
				craftedItems.push_back(std::make_unique<RockAxe>());
				std::cout << "Crafted a Rock Axe\n";
			}
			else std::cout << "Not enough resources\n";
		}

		else if (itemName == "rock shovel")
		{
			if (m_pWood >= 2 && m_pRock >= 1) 
			{
				m_pWood -= 2;; m_pRock -= 1;
				craftedItems.push_back(std::make_unique<RockShovel>());
				std::cout << "Crafted a Rock Shovel\n";
			}
			else std::cout << "Not enough resources\n";
		}

		else 
		{
			std::cout << "Unknown recipe: " << itemName << "\n";
		}
	}

	void craftArmor(const std::string& armorName)
	{
		if (armorName == "iron armor")
		{
			if (m_pIron >= 24)
			{
				m_pWood -= 24;
				craftedArmor.push_back(std::make_unique<IronArmor>());
				std::cout << "Forged a set of Iron Armor\n";
			}
			else std::cout << "Not enough iron\n";
		}

		else
		{
			std::cout << "Unknown recipe: " << armorName << "\n";
		}
	}

	// Equiping Functions

	void equipItem(const std::string& itemName)
	{
		std::string input = itemName;
		for (auto& c : input) c = static_cast<char>(tolower(c));

		auto it = std::find_if(craftedItems.begin(), craftedItems.end(),
			[&](const std::unique_ptr<Items>& item)
			{
				std::string itemStr = item->displayItems();
				for (auto& c : itemStr) c = static_cast<char>(tolower(c));
				return itemStr == input;
			});

		if (it != craftedItems.end())
		{
			if (equippedItem)
			{
				std::cout << "Unequipped " << equippedItem->displayItems() << ".\n";
			}
			equippedItem = it->get();
			std::cout << "Equipped " << equippedItem->displayItems() << "!\n";
		}

		else
		{
			std::cout << "You don’t have a " << itemName << " to equip.\n";
		}
	}

	void equipArmor(const std::string& armorName)
	{
		std::string input = armorName;
		for (auto& c : input) c = static_cast<char>(tolower(c));

		auto it = std::find_if(craftedArmor.begin(), craftedArmor.end(),
			[&](const std::unique_ptr<Items>& item)
			{
				std::string itemStr = item->displayItems();
				for (auto& c : itemStr) c = static_cast<char>(tolower(c));
				return itemStr == input;
			});

		if (it != craftedArmor.end())
		{
			if (equippedArmor)
			{
				std::cout << "Unequipped " << equippedArmor->displayItems() << ".\n";
			}
			equippedArmor = it->get();
			std::cout << "Equipped " << equippedArmor->displayItems() << "!\n";
		}

		else
		{
			std::cout << "You don’t have a " << armorName << " to equip.\n";
		}
	}

	// Use Items

	void eatApple()
	{
		if (m_pApples <= 0)
		{
			std::cout << "You have no apples to eat.\n";
			return;
		}

		if (m_pHealth >= 10)
		{
			std::cout << "You ate an apple.\n";
			m_pApples -= 1;
		}

		else
		{
			std::cout << "You ate an apple and gained some health.\n";
			m_pHealth += 2;
			if (m_pHealth > 10)
			{
				m_pHealth = 10;
			}
			m_pApples -= 1;
		}
	}

	inline void useFurnace(const std::string& input, int amount = 1) {
		std::string cmd = input;
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

		if (cmd != "iron") {
			std::cout << "You can only smelt iron here.\n";
			return;
		}

		auto it = std::find_if(craftedItems.begin(), craftedItems.end(),
			[](const std::unique_ptr<Items>& item) {
				return item->displayItems() == "Furnace";
			});

		if (it == craftedItems.end()) 
		{
			std::cout << "You don’t have a furnace to use.\n";
			return;
		}

		if (amount < 1) 
		{
			std::cout << "Invalid amount.\n";
			return;
		}

		if (amount > 100) amount = 100;

		if (m_pIronOre < amount || m_pCoal < amount) 
		{
			std::cout << "Not enough materials to smelt " << amount << " iron.\n";
			return;
		}

		m_pIron += amount;
		m_pIronOre -= amount;
		m_pCoal -= amount;
		m_pScore += amount * 20;

		std::cout << "Smelted " << amount << " iron and gained " << amount * 20 << " score!\n";
	}




	// Getters

	int getPlayerHealth() const
	{
		return m_pHealth;
	}

	int getPlayerStamina() const
	{
		return m_pStamina;
	}

	int getPlayerAttack() const
	{
		int attack = m_pAttack;
		if (equippedItem)
			attack += equippedItem->getMobAttack();
		return attack;
	}

	int getMiningPower() const
	{
		int power = 1;
		if (equippedItem)
			power += equippedItem->getItemAttack();
		return power;
	}

	void getIronOre() const
	{
		 std::cout << "Iron Ore: " << m_pIronOre << "\n";
	}

	void getCoal() const
	{
		std::cout << "Coal: " << m_pCoal << "\n";
	}

	int getPlayerScore() const
	{
		return m_pScore;
	}

	int getPlayerX() const
	{
		return m_pPosX;
	}

	int getPlayerY() const
	{
		return m_pPosY;
	}

	void setPlayerPosition(int x, int y)
	{
		m_pPosX = x, m_pPosY = y;
	}

	void takeDamage(int damage)
	{
		int defense = 0;
		if (equippedArmor)
			defense += equippedArmor->getArmorHealth();

		int damageTaken = damage - defense;
		if (damageTaken < 0) damageTaken = 0;

		m_pHealth -= damageTaken;
		if (m_pHealth < 0) m_pHealth = 0;
	}

	// Using and Gaining Stamina
	void useStamina(int amount) 
	{
		m_pStamina -= amount;
	}

	void rest() 
	{
		if (m_pStamina >= 10) 
		{
			std::cout << "You are fully rested!\n";
			return;
		}

		else
		{
			std::cout << "You have rested and recoverd some of your stamina.\n";
			m_pStamina += 2;
			if (m_pStamina > 10)
			{
				m_pStamina = 10;
			}
		}
	}

	// Player Gains Stuff

	void gainScore(int amount)
	{
		m_pScore += amount;
	}


	void gainWood(int amount) 
	{
		m_pWood += amount;
	}

	void gainApples(int amount)
	{
		m_pApples += amount;
	}

	void gainAcorns(int amount) 
	{
		m_pAcorns += amount;
	}

	void gainSlimeBalls(int amount)
	{
		m_pSlimeBalls += amount;
	}

	void gainRock(int amount)
	{
		m_pRock += amount;
	}

	void gainCoal(int amount) 
	{
		m_pCoal += amount;
	}

	void gainIronOre(int amount)
	{
		m_pIronOre += amount;
	}

	void gainIron(int amount)
	{
		m_pIron += amount;
	}

	// Check if player health is above 0

	bool isAlive() const
	{
		return m_pHealth > 0;
	}

protected:

	// Player Stats

	int m_pHealth;
	int m_pMaxHealth;
	int m_pStamina;
	int m_pMaxStamina;
	int m_pAttack;
	int m_pPosX;
	int m_pPosY;
	int m_pScore;

	// Player Inventory

	int m_pWood;
	int m_pApples;
	int m_pAcorns;
	int m_pSlimeBalls;
	int m_pRock;
	int m_pCoal;
	int m_pIronOre;
	int m_pIron;

	// Crafted Items

	std::vector<std::unique_ptr<Items>> craftedItems;
	Items* equippedItem;

	// Crafted Armor

	std::vector<std::unique_ptr<Items>> craftedArmor;
	Items* equippedArmor;
};

// Mobs

class Mob 
{
public: 
	Mob(const std::string& name) : m_mName(name), m_mHealth(10), m_mAttack(0)
	{

	}

	int getMobAttack() const
	{
		return m_mAttack;
	}

	void takeDamage(int damage) {
		int damageTaken = damage;
		if (damageTaken < 0) damageTaken = 0;
		m_mHealth -= damageTaken;
		if (m_mHealth < 0) m_mHealth = 0;
	}

	bool isAlive() const
	{
		return m_mHealth > 0;
	}

protected:
	std::string m_mName;
	int m_mHealth;
	int m_mAttack;
};

class Slime : public Mob 
{
public:
	Slime() : Mob("Slime")
	{
		m_mHealth -= 2;
		m_mAttack += 1;
	}
};

class BossSlime : public Mob
{
public:
	BossSlime() : Mob("Boss Slime")
	{
		m_mAttack += 2;
	}
};

class Zombie : public Mob
{
public:
	Zombie() : Mob("Zombie")
	{
		m_mAttack += 2;
	}
};

class Creeper : public Mob
{
public:
	Creeper() : Mob("Creeper")
	{
		m_mHealth -= 5;
		m_mAttack += 4;
	}
};

// Boss: If killed by player, they will win the game

class AirWizard : public Mob
{
public:
	AirWizard() : Mob("Air Wizard")
	{
		m_mHealth += 2;
		m_mAttack += 5;
	}
};

// Minable items like a tree

class MinableItems 
{
public:
	MinableItems(const std::string& name) : m_miName(), m_miHealth(0)
	{

	}

	void takeDamage(int damage) {
		int damageTaken = damage;
		if (damageTaken < 0) damageTaken = 0;
		m_miHealth -= damageTaken;
		if (m_miHealth < 0) m_miHealth = 0;
	}

	bool isAlive() const
	{
		return m_miHealth > 0;
	}

protected:
	std::string m_miName;
	int m_miHealth;
 };

class Tree : public MinableItems
{
public:
	Tree() : MinableItems("Tree")
	{
		m_miHealth += 6;
	}
};

class Rock : public MinableItems
{
public:
	Rock() : MinableItems("Rock")
	{
		m_miHealth += 10;
	}
};

class Coal : public MinableItems
{
public:
	Coal() : MinableItems("Coal")
	{
		m_miHealth += 12;
	}
};

class Iron : public MinableItems
{
public:
	Iron() : MinableItems("Iron")
	{
		m_miHealth += 15;
	}
};


#endif // !ENTITY_H
