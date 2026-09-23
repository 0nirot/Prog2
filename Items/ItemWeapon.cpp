#include "ItemWeapon.h"

ItemWeapon::ItemWeapon()
{
	damage = 20;
}

ItemWeapon::~ItemWeapon()
{
}

int ItemWeapon::getDamage() const
{
	return damage;
}

void ItemWeapon::setDamage(int damage)
{
	this->damage = damage;
}
