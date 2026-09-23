#include "Character.h"
#include "EquipmentContainer.h"
#include "Items\ItemEquippable.h"
#include "Items\ItemWeapon.h"
#include "Items\ItemArmor.h"
#include "Items\ItemTrinket.h"
#include "Map.h"
#include "TileTreasure.h"
#include "TileTraversable.h"


Character::Character()
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

void Character::pickUpItem()
{
	auto tile = currentMap->getTile(getX(), getY());

		if (auto treasureTile = std::dynamic_pointer_cast<TileTreasure>(tile))
		{
			std::shared_ptr<ItemBase> loot = treasureTile->getLoot();
			if (loot)
			{
				int slot = inventory->addBagItem(loot);
				if (slot < 0)
				{
					printf("Inventory full, cannot pick up: %s\n", loot->getName().c_str());
					return;
				}

				std::shared_ptr<TileTraversable> newTile = std::make_shared<TileTraversable>();
				currentMap->setTile(getX(), getY(), newTile);
				newTile->setPlayerOnTile(true);
				printf("Picked up: %s\n", loot->getName().c_str());
			}
		}
}
