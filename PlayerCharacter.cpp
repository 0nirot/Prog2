#include "PlayerCharacter.h"
#include "ItemBase.h"

PlayerCharacter::PlayerCharacter(int strength)
	: Character(), strength(strength)
{
}

PlayerCharacter::~PlayerCharacter()
{
}

int PlayerCharacter::getStrength() const
{
	return strength;
}

void PlayerCharacter::setStrength(int s)
{
	strength = s;
}

float PlayerCharacter::getMaxCarryWeight() const
{
	return static_cast<float>(strength) * 2.0f;
}

bool PlayerCharacter::isOverWeight() const
{
	return (getInventory()->getTotalWeight() > getMaxCarryWeight());
}

bool PlayerCharacter::tryAddToBag(std::shared_ptr<ItemBase> item)
{
	if (!item)
		return false;
	if (!isOverWeight())
		return false;

	return getInventory()->addBagItem(item) >= 0;
}
