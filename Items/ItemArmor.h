#pragma once
#include "ItemEquippable.h"

class ItemArmor : public ItemEquippable
{
public:
	ItemArmor();
	~ItemArmor();

	int getDefense() const;
	void setDefense(int defense);

protected:
	int defense;
};
