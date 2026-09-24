#pragma once
#include "ItemBase.h"

class Stick : public ItemBase
{
public:
	Stick();
	~Stick();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<Stick>(*this); }
};
