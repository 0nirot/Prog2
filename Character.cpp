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
	: strength(0.0f)
{
	std::vector<SlotType<ItemEquippable>> equipmentLayout = {
		makeSlotType<ItemWeapon>("Weapon"),
		makeSlotType<ItemArmor>("Armor"),
		makeSlotType<ItemTrinket>("Trinket")
	};
	// this als nicht-besitzender Owner: das Inventar lebt nie länger als der Character
	m_inventory = std::make_shared<Inventory<ItemBase, ItemEquippable>>(10, equipmentLayout, this);
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

				std::shared_ptr<TileTraversable> newTile = std::make_shared<TileTraversable>();
				currentMap->setTile(getX(), getY(), newTile);
				newTile->setPlayerOnTile(true);
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

float Character::getStrength() const
{
	return strength;
}

void Character::setStrength(float newStrength)
{
	strength = newStrength;
}
