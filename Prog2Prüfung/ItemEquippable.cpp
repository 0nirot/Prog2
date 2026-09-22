#include "ItemEquippable.h"

ItemEquippable::ItemEquippable()
	: ItemBase(), equipped(false), strengthBonus(0)
{
}

ItemEquippable::ItemEquippable(const std::string& name, const std::string& description, float weight, int value)
	: ItemBase(name, description, weight, value), equipped(false), strengthBonus(0)
{
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
