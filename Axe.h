#pragma once
#include "ItemWeapon.h"

class Axe : public ItemWeapon
{
public:
	Axe();
	explicit Axe(const std::string& name, const std::string& description, float weight, int value, int damage);
	~Axe();
};
