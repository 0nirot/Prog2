#pragma once
#include "ItemBase.h"

class ItemEquippable : public ItemBase
{
public:
	ItemEquippable();
	explicit ItemEquippable(const std::string& name, const std::string& description, float weight, int value);
	~ItemEquippable();

	bool isEquipped() const;
	void setEquipped(bool equipped);

	int getArmorBonus() const;
	void setArmorBonus(int armorBonus);

private:
	bool equipped;
	int strengthBonus;
};
