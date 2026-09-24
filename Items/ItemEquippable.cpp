#include "ItemEquippable.h"

ItemEquippable::ItemEquippable()
{
	equipped = false;
	strengthBonus = 0.0f;
}

ItemEquippable::~ItemEquippable()
{
}

bool ItemEquippable::isEquipped() const
{
	return equipped;
}

void ItemEquippable::setEquipped(bool newEquipped)
{
	equipped = newEquipped;
}

float ItemEquippable::getStrengthBonus() const
{
	return strengthBonus;
}

void ItemEquippable::setStrengthBonus(float newStrengthBonus)
{
	strengthBonus = newStrengthBonus;
}
