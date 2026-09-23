#pragma once
#include "ItemEquippable.h"

class ItemArmor : public ItemEquippable
{
public:
	ItemArmor();
	explicit ItemArmor(const std::string& name, const std::string& description, float weight, int value, int defense);
	~ItemArmor();

	int getDefense() const;
	void setDefense(int defense);

private:
	int defense;
};
