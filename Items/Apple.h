#pragma once
#include "ItemBase.h"

class Apple : public ItemBase
{
public:
	Apple();
	~Apple();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<Apple>(*this); }
};
