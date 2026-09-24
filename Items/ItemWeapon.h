#pragma once
#include "ItemEquippable.h"

class ItemWeapon : public ItemEquippable
{
public:
	ItemWeapon();
	~ItemWeapon();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<ItemWeapon>(*this); }

	int getDamage() const;
	void setDamage(int damage);

protected:
	int damage;
};
