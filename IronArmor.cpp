#include "IronArmor.h"

IronArmor::IronArmor()
	: ItemArmor("Iron Armor", "A suit of durable iron armor, forged by skilled blacksmiths", 18.0f, 250, 28)
{
}

IronArmor::IronArmor(const std::string& name, const std::string& description, float weight, int value, int defense)
	: ItemArmor(name, description, weight, value, defense)
{
}

IronArmor::~IronArmor()
{
}
