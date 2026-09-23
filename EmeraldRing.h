#pragma once
#include "ItemTrinket.h"

class EmeraldRing : public ItemTrinket
{
public:
	EmeraldRing();
	explicit EmeraldRing(const std::string& name, const std::string& description, float weight, int value, int magicBonus);
	~EmeraldRing();
};
