#pragma once
#include "ItemWeapon.h"

class Sword : public ItemWeapon
{
public:
	Sword();
	explicit Sword(const std::string& name, const std::string& description, float weight, int value, int damage);
	~Sword();
};
