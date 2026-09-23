#include "ItemTrinket.h"

ItemTrinket::ItemTrinket()
{
	magicBonus = 5;
}

ItemTrinket::~ItemTrinket()
{
}

int ItemTrinket::getMagicBonus() const
{
	return magicBonus;
}

void ItemTrinket::setMagicBonus(int magicBonus)
{
	this->magicBonus = magicBonus;
}
