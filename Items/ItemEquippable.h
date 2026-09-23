#pragma once
#include "ItemBase.h"

class ItemEquippable : public ItemBase
{
public:
	ItemEquippable();
	~ItemEquippable();

	bool isEquipped() const;
	void setEquipped(bool equipped);

	int getArmorBonus() const;
	void setArmorBonus(int armorBonus);

private:
	bool equipped;
	int strengthBonus;
};
