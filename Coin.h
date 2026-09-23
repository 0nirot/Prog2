#pragma once
#include "ItemBase.h"

class Coin : public ItemBase
{
public:
	Coin();
	explicit Coin(const std::string& name, const std::string& description, float weight, int value);
	~Coin();
};
