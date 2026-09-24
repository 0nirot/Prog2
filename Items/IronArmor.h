#pragma once
#include "ItemArmor.h"

class IronArmor : public ItemArmor
{
public:
	IronArmor();
	~IronArmor();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<IronArmor>(*this); }
};
