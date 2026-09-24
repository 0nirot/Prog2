#include "Character.h"
#include "EquipmentContainer.h"
#include "Items\ItemEquippable.h"
#include "Items\ItemWeapon.h"
#include "Items\ItemArmor.h"
#include "Items\ItemTrinket.h"
#include "Map.h"
#include "TileTreasure.h"
#include "TileTraversable.h"
#include <cstdio>


Character::Character()
	: strength(0.0f)
{
	std::vector<SlotType<ItemEquippable>> equipmentLayout = {
		makeSlotType<ItemWeapon>("Weapon"),
		makeSlotType<ItemArmor>("Armor"),
		makeSlotType<ItemTrinket>("Trinket")
	};
	m_inventory = std::make_shared<Inventory<ItemBase, ItemEquippable>>(10, equipmentLayout, this);
}

Character::~Character()
{
}

void Character::moveUp()
{
	moveTo(getX(), getY() - 1);
}

void Character::moveDown()
{
	moveTo(getX(), getY() + 1);
}

void Character::moveLeft()
{
	moveTo(getX() - 1, getY());
}

void Character::moveRight()
{
	moveTo(getX() + 1, getY());
}

bool Character::moveTo(int newX, int newY)
{
	if (!isMovePossible(newX, newY, *currentMap))
		return false;

	currentMap->getTile(getX(), getY())->setPlayerOnTile(false);
	posx = newX;
	posy = newY;
	currentMap->getTile(getX(), getY())->setPlayerOnTile(true);
	return true;
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

std::shared_ptr<Inventory<ItemBase, ItemEquippable>> Character::getInventory() const
{
	return m_inventory;
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
				int slot = m_inventory->addBagItem(loot);
				if (slot < 0)
				{
					printf("Inventory full, cannot pick up: %s\n", loot->getName().c_str());
					return;
				}

				clearTreasureTile();
				printf("Picked up: %s\n", loot->getName().c_str());
			}
		}
}

void Character::dropItem()
{
	auto selectedItem = m_inventory->getBagItem(m_inventory->getSelectedSlotIndex());
	if (!selectedItem)
	{
		printf("No item selected to drop\n");
		return;
	}
	auto tile = currentMap->getTile(getX(), getY());
	if (tile && std::dynamic_pointer_cast<TileTraversable>(tile))
	{
		std::shared_ptr<TileTreasure> treasureTile = std::make_shared<TileTreasure>();
		treasureTile->setLoot(selectedItem);
		currentMap->setTile(getX(), getY(), treasureTile);
		treasureTile->setPlayerOnTile(true);
		m_inventory->removeBagItem(m_inventory->getSelectedSlotIndex());
		printf("Dropped: %s\n", selectedItem->getName().c_str());
	}
	else
	{
		printf("Cannot drop item here, tile is not traversable\n");
	}
}

void Character::changeInventorySlot(int offset)
{
	m_inventory->selectNextSlot(offset);
}

void Character::equipItem()
{
	if (!m_inventory->equipSelectedItem())
	{
		printf("Selected item cannot be equipped\n");
	}
}

void Character::clearTreasureTile()
{
	std::shared_ptr<TileTraversable> newTile = std::make_shared<TileTraversable>();
	currentMap->setTile(getX(), getY(), newTile);
	newTile->setPlayerOnTile(true);
}

float Character::getStrength() const
{
	return strength;
}

void Character::setStrength(float newStrength)
{
	strength = newStrength;
}

float Character::getMaxCarryWeight() const
{
	return strength * 2.0f;
}

bool Character::isOverWeight() const
{
	return m_inventory->getTotalWeight() >= getMaxCarryWeight();
}

bool Character::canCarry(std::shared_ptr<ItemBase>& item) const
{
	return m_inventory->getTotalWeight() + item->getWeight() < getMaxCarryWeight();
}

bool Character::autoWalk(float stepDelay)
{
	if (isOverWeight())
	{
		printf("Too heavy to walk\n");
		return false;
	}

	PathFinder pathFinder;
	autoWalkPath = pathFinder.findPathToExit(*currentMap, { posx, posy });
	if (autoWalkPath.empty())
	{
		printf("No path to exit found\n");
		return false;
	}

	autoWalkIndex = 1;
	autoWalkStepDelay = stepDelay;
	autoWalkTimer = 0.0f;
	printf("Auto walk started: %d steps\n", static_cast<int>(autoWalkPath.size()) - 1);
	return true;
}

void Character::updateAutoWalk(float deltaTime)
{
	if (!isAutoWalking())
		return;

	// Delay zwischen den Schritten, damit man die Figur laufen sieht
	autoWalkTimer += deltaTime;
	if (autoWalkTimer < autoWalkStepDelay)
		return;
	autoWalkTimer = 0.0f;

	if (isOverWeight())
	{
		printf("Too heavy, auto walk stopped\n");
		stopAutoWalk();
		return;
	}

	const GridPosition next = autoWalkPath[autoWalkIndex];
	if (!moveTo(next.x, next.y))
	{
		printf("Path blocked, auto walk stopped\n");
		stopAutoWalk();
		return;
	}
	++autoWalkIndex;

	autoPickUpItem();

	if (!isAutoWalking())
	{
		printf("Exit reached\n");
		stopAutoWalk();
	}
}

void Character::stopAutoWalk()
{
	autoWalkPath.clear();
	autoWalkIndex = 0;
	autoWalkTimer = 0.0f;
}

bool Character::isAutoWalking() const
{
	return autoWalkIndex > 0 && autoWalkIndex < autoWalkPath.size();
}

void Character::autoPickUpItem()
{
	auto treasureTile = std::dynamic_pointer_cast<TileTreasure>(currentMap->getTile(posx, posy));
	if (!treasureTile)
		return;

	std::shared_ptr<ItemBase> loot = treasureTile->getLoot();
	if (!loot)
		return;

	if (!canCarry(loot))
	{
		printf("Too heavy, left behind: %s\n", loot->getName().c_str());
		return;
	}

	const int bagSlot = m_inventory->addBagItem(loot);
	if (bagSlot < 0)
	{
		printf("Inventory full, left behind: %s\n", loot->getName().c_str());
		return;
	}

	clearTreasureTile();
	printf("Auto picked up: %s\n", loot->getName().c_str());

	auto equippable = std::dynamic_pointer_cast<ItemEquippable>(loot);
	if (equippable && m_inventory->isBetterThanEquipped(equippable))
	{
		m_inventory->equip(static_cast<std::size_t>(bagSlot));
		printf("Auto equipped: %s (+%.1f strength)\n", loot->getName().c_str(), equippable->getStrengthBonus());
	}
}
