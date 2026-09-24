#include "PlayerCharacter.h"
#include "Items\ItemBase.h"

PlayerCharacter::PlayerCharacter()
{
	strength = 10;
}

PlayerCharacter::~PlayerCharacter()
{
}

float PlayerCharacter::getMaxCarryWeight() const
{
	return static_cast<float>(strength) * 2.0f;
}

bool PlayerCharacter::isOverWeight() const
{
	return (getInventory()->getTotalWeight() >= getMaxCarryWeight());
}

bool PlayerCharacter::tryAddToBag(std::shared_ptr<ItemBase> item)
{
	if (!item)
		return false;
	if (isOverWeight())
		return false;

	return getInventory()->addBagItem(item) >= 0;
}