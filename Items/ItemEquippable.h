#pragma once
#include "ItemBase.h"

class ItemEquippable : public ItemBase
{
public:
	ItemEquippable();
	~ItemEquippable();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<ItemEquippable>(*this); }

	bool isEquipped() const;
	void setEquipped(bool equipped);

	float getStrengthBonus() const;
	void setStrengthBonus(float strengthBonus);

protected:
	bool equipped;
	float strengthBonus;
};
