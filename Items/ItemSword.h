#pragma once
#include "ItemBase.h"

class ItemSword : public ItemBase
{
public:
	ItemSword();
	~ItemSword();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<ItemSword>(*this); }

	int getDamage() const;
	void setDamage(int damage);

private:
	int damage;
};
