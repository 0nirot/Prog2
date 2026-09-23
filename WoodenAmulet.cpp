#include "WoodenAmulet.h"

WoodenAmulet::WoodenAmulet()
	: ItemTrinket("Wooden Amulet", "An ancient amulet carved from sacred wood, glowing with magical energy", 0.2f, 80, 6)
{
}

WoodenAmulet::WoodenAmulet(const std::string& name, const std::string& description, float weight, int value, int magicBonus)
	: ItemTrinket(name, description, weight, value, magicBonus)
{
}

WoodenAmulet::~WoodenAmulet()
{
}
