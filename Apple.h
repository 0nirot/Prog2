#pragma once
#include "ItemBase.h"

class Apple : public ItemBase
{
public:
	Apple();
	explicit Apple(const std::string& name, const std::string& description, float weight, int value);
	~Apple();
};
