#include "PlotArmor.h"

PlotArmor::PlotArmor()
	: ItemArmor("Plot Armor", "A legendary armor that protects the protagonist through the power of narrative", 12.0f, 300, 35)
{
}

PlotArmor::PlotArmor(const std::string& name, const std::string& description, float weight, int value, int defense)
	: ItemArmor(name, description, weight, value, defense)
{
}

PlotArmor::~PlotArmor()
{
}
