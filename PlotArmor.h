#pragma once
#include "ItemArmor.h"

class PlotArmor : public ItemArmor
{
public:
	PlotArmor();
	explicit PlotArmor(const std::string& name, const std::string& description, float weight, int value, int defense);
	~PlotArmor();
};
