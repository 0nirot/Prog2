#pragma once
#include "ItemEquippable.h"

class ItemArmor : public ItemEquippable
{
public:
	ItemArmor();
	~ItemArmor();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<ItemArmor>(*this); }

	int getDefense() const;
	void setDefense(int defense);

protected:
	int defense;
};
