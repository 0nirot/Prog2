#pragma once
#include "ItemBase.h"

class Stick : public ItemBase
{
public:
	Stick();
	explicit Stick(const std::string& name, const std::string& description, float weight, int value);
	~Stick();
};
