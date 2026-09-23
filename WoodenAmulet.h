#pragma once
#include "ItemTrinket.h"

class WoodenAmulet : public ItemTrinket
{
public:
	WoodenAmulet();
	explicit WoodenAmulet(const std::string& name, const std::string& description, float weight, int value, int magicBonus);
	~WoodenAmulet();
};
