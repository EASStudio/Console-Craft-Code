#pragma once
#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>

class Items
{
public:
	Items(const std::string& name)
		: m_iName(name), m_iMobAttack(0), m_iItemAttack(0), m_iArmorHealth(0)
	{

	}
	  // When attacking a enemy
	  int getMobAttack() const
	  {
		  return m_iMobAttack;
	  }

	  // When mining a item
	  int getItemAttack() const
	  {
		  return m_iItemAttack;
	  }

	  int getArmorHealth() const
	  {
		  return m_iArmorHealth;
	  }

	  std::string displayItems() const 
	  {
		  return m_iName;
	  }

protected:
	std::string m_iName;

	// When attacking a enemy

	int m_iMobAttack;

	// When mining a item

	int m_iItemAttack;

	// For Armor

	int m_iArmorHealth;
};

// Crafting Items

class CraftingBench : public Items
{
public:
	CraftingBench() : Items("Crafting Bench")
	{

	}
};

class Goo : public Items
{
public:
	Goo() : Items("Goo")
	{

	}
};

class Anvil : public Items
{
public:
	Anvil() : Items("Anvil")
	{

	}
};

class Furnace : public Items
{
public:
	Furnace() : Items("Furnace")
	{

	}
};

// Default Tools

class PowGlove : public Items
{
public:
	PowGlove() : Items("Pow Glove")
	{
		m_iMobAttack += 1;
		m_iItemAttack += 1;
	}
};

// Wood Tools

class WoodSword : public Items
{
public:
	WoodSword() : Items("Wood Sword")
	{
		m_iMobAttack += 2;
		m_iItemAttack += 1;
	}
};

class WoodPick : public Items
{
public:
	WoodPick() : Items("Wood Pick")
	{
		m_iMobAttack += 1;
		m_iItemAttack += 2;
	}
};

class WoodAxe : public Items
{
public:
	WoodAxe() : Items("Wood Axe")
	{
		m_iMobAttack += 1;
		m_iItemAttack += 2;
	}
};

class WoodShovel : public Items
{
public:
	WoodShovel() : Items("Wood Shovel")
	{
		m_iMobAttack += 1;
		m_iItemAttack += 2;
	}
};

// Rock Tools

class RockSword : public Items
{
public:
	RockSword() : Items("Rock Sword")
	{
		m_iMobAttack += 3;
		m_iItemAttack += 1;
	}
};

class RockPick : public Items
{
public:
	RockPick() : Items("Rock Pick")
	{
		m_iMobAttack += 1;
		m_iItemAttack += 3;
	}
};

class RockAxe : public Items
{
public:
	RockAxe() : Items("Rock Axe")
	{
		m_iMobAttack += 2;
		m_iItemAttack += 3;
	}
};

class RockShovel : public Items
{
public:
	RockShovel() : Items("Rock Shovel")
	{
		m_iMobAttack += 1;
		m_iItemAttack += 3;
	}
};

// Iron Armor

class IronArmor : public Items
{
public:
	IronArmor() : Items("Iron Armor")
	{
		m_iArmorHealth += 10;
	}
};

#endif // !ITEMS_H
