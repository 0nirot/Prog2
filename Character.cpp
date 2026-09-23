#include "Character.h"
#include "EquipmentContainer.h"
#include "ItemEquippable.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"
#include "ItemTrinket.h"
#include "Map.h"


Character::Character()
	: name("Peter"), posx(0), posy(0), health(100), maxHealth(100)
{
	std::vector<SlotType<ItemEquippable>> equipmentLayout = {
		makeSlotType<ItemWeapon>("Weapo"),
		makeSlotType<ItemArmor>("Armor"),
		makeSlotType<ItemTrinket>("Trinket")
	};
	inventory = std::make_shared<Inventory<ItemBase, ItemEquippable>>(10, equipmentLayout);

}

Character::~Character()
{
}

void Character::moveUp()
{
	if (isMovePossible(getX(), getY() - 1, *currentMap))
	{
		currentMap->getTile(getX(), getY())->setPlayerOnTile(false);
		posy--;
		currentMap->getTile(getX(), getY())->setPlayerOnTile(true);
		
	}
}

void Character::moveDown()
{
	if (isMovePossible(getX(), getY() + 1, *currentMap))
	{
		currentMap->getTile(getX(), getY())->setPlayerOnTile(false);
		posy++;
		currentMap->getTile(getX(), getY())->setPlayerOnTile(true);
	}
}

void Character::moveLeft()
{
	if (isMovePossible(getX() - 1, getY(), *currentMap))
	{
		currentMap->getTile(getX(), getY())->setPlayerOnTile(false);
		posx--;
		currentMap->getTile(getX(), getY())->setPlayerOnTile(true);
	}
}

void Character::moveRight()
{
	if (isMovePossible(getX() + 1, getY(), *currentMap))
	{
		currentMap->getTile(getX(), getY())->setPlayerOnTile(false);
		posx++;
		currentMap->getTile(getX(), getY())->setPlayerOnTile(true);
	}
}

int Character::getX() const
{
	return posx;
}

int Character::getY() const
{
	return posy;
}

void Character::setPosition(int x, int y)
{
	posx = x;
	posy = y;
}

const std::string& Character::getName() const
{
	return name;
}

void Character::setName(const std::string& name)
{
	this->name = name;
}

int Character::getHealth() const
{
	return health;
}

void Character::setHealth(int health)
{
	this->health = health;
}

int Character::getMaxHealth() const
{
	return maxHealth;
}

void Character::setMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}

void Character::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
		health = 0;
}

void Character::heal(int amount)
{
	health += amount;
	if (health > maxHealth)
		health = maxHealth;
}

std::shared_ptr<Inventory<ItemBase, ItemEquippable>> Character::getInventory() const
{
	return inventory;
}

void Character::setCurrentMap(std::shared_ptr<Map> map)
{
	currentMap = map;
}
