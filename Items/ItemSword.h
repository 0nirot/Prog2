#pragma once
#include "ItemBase.h"

class ItemSword : public ItemBase
{
public:
	ItemSword();
	~ItemSword();

	int getDamage() const;
	void setDamage(int damage);

private:
	int damage;
};
