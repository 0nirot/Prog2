#pragma once
#include "ItemTrinket.h"

class WoodenAmulet : public ItemTrinket
{
public:
	WoodenAmulet();
	~WoodenAmulet();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<WoodenAmulet>(*this); }
};
