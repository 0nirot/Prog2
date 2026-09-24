#include "PlayerCharacter.h"
#include "Items\ItemBase.h"

PlayerCharacter::PlayerCharacter()
{
	strength = 10;
}

PlayerCharacter::~PlayerCharacter()
{
}

bool PlayerCharacter::tryAddToBag(std::shared_ptr<ItemBase> item)
{
	if (!item)
		return false;
	if (isOverWeight())
		return false;

	return getInventory()->addBagItem(item) >= 0;
}