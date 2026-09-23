#pragma once
#include "ItemEquippable.h"

class ItemTrinket : public ItemEquippable
{
public:
	ItemTrinket();
	~ItemTrinket();

	int getMagicBonus() const;
	void setMagicBonus(int magicBonus);

protected:
	int magicBonus;
};
