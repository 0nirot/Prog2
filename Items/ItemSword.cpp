#include "ItemSword.h"

ItemSword::ItemSword()
{
	name = "Sword";
	damage = 10;
	description = "Sharp and Shiny.";
	weight = 5.0f;
	value = 100;
}

ItemSword::~ItemSword()
{
}

int ItemSword::getDamage() const
{
	return damage;
}

void ItemSword::setDamage(int newDamage)
{
	damage = newDamage;
}
