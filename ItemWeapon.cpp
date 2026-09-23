#include "ItemWeapon.h"

ItemWeapon::ItemWeapon()
	: ItemEquippable("Longsword", "Ein langes Schwert", 3.0f, 180), damage(20)
{
}

ItemWeapon::ItemWeapon(const std::string& name, const std::string& description, float weight, int value, int damage)
	: ItemEquippable(name, description, weight, value), damage(damage)
{
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
