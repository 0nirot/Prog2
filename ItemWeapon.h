#pragma once
#include "ItemEquippable.h"

class ItemWeapon : public ItemEquippable
{
public:
	ItemWeapon();
	explicit ItemWeapon(const std::string& name, const std::string& description, float weight, int value, int damage);
	~ItemWeapon();

	int getDamage() const;
	void setDamage(int damage);

private:
	int damage;
};
