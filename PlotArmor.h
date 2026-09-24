#pragma once
#include "Items/ItemArmor.h"

class PlotArmor : public ItemArmor
{
public:
	PlotArmor();
	~PlotArmor();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<PlotArmor>(*this); }
};
