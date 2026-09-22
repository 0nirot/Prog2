#pragma once
#include "ItemEquippable.h"

class ItemTrinket : public ItemEquippable
{
public:
	ItemTrinket();
	explicit ItemTrinket(const std::string& name, const std::string& description, float weight, int value, int magicBonus);
	~ItemTrinket();

	int getMagicBonus() const;
	void setMagicBonus(int magicBonus);

private:
	int magicBonus;
};
