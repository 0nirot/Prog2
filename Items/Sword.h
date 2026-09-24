#pragma once
#include "ItemWeapon.h"

class Sword : public ItemWeapon
{
public:
	Sword();
	~Sword();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<Sword>(*this); }
};
