#pragma once
#include "ItemWeapon.h"

class Axe : public ItemWeapon
{
public:
	Axe();
	~Axe();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<Axe>(*this); }
};
