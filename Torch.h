#pragma once
#include "ItemBase.h"

class Torch : public ItemBase
{
public:
	Torch();
	explicit Torch(const std::string& name, const std::string& description, float weight, int value);
	~Torch();
};
