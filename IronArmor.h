#pragma once
#include "ItemArmor.h"

class IronArmor : public ItemArmor
{
public:
	IronArmor();
	explicit IronArmor(const std::string& name, const std::string& description, float weight, int value, int defense);
	~IronArmor();
};
