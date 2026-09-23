#pragma once
#include "ItemEquippable.h"

class ItemWeapon : public ItemEquippable
{
public:
	ItemWeapon();
	~ItemWeapon();

	int getDamage() const;
	void setDamage(int damage);

protected:
	int damage;
};
