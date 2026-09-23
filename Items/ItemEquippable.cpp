#include "ItemEquippable.h"

ItemEquippable::ItemEquippable()
{
	equipped = false;
	strengthBonus = 0;
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

int ItemEquippable::getArmorBonus() const
{
	return strengthBonus;
}

void ItemEquippable::setArmorBonus(int newArmorBonus)
{
	strengthBonus = newArmorBonus;
}
