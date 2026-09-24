#pragma once
#include "ItemBase.h"

class Torch : public ItemBase
{
public:
	Torch();
	~Torch();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<Torch>(*this); }
};
