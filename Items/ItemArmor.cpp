#include "ItemArmor.h"

ItemArmor::ItemArmor()
{
	defense = 25;
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
