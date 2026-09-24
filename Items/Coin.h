#pragma once
#include "ItemBase.h"

class Coin : public ItemBase
{
public:
	Coin();
	~Coin();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<Coin>(*this); }
};
