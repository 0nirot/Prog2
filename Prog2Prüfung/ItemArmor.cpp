#include "ItemArmor.h"

ItemArmor::ItemArmor()
	: ItemEquippable("Iron Breastplate", "Eine Eisenruestung", 15.0f, 200), defense(25)
{
}

ItemArmor::ItemArmor(const std::string& name, const std::string& description, float weight, int value, int defense)
	: ItemEquippable(name, description, weight, value), defense(defense)
{
}

ItemArmor::~ItemArmor()
{
}

int ItemArmor::getDefense() const
{
	return defense;
}

void ItemArmor::setDefense(int defense)
{
	this->defense = defense;
}
