#pragma once
#include "ItemEquippable.h"

class ItemTrinket : public ItemEquippable
{
public:
	ItemTrinket();
	~ItemTrinket();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<ItemTrinket>(*this); }

	int getMagicBonus() const;
	void setMagicBonus(int magicBonus);

protected:
	int magicBonus;
};
