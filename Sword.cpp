#include "Sword.h"

Sword::Sword()
	: ItemWeapon("Sword", "Sharp and shiny", 2.5f, 150, 18)
{
}

Sword::Sword(const std::string& name, const std::string& description, float weight, int value, int damage)
	: ItemWeapon(name, description, weight, value, damage)
{
}

Sword::~Sword()
{
}
