#include "Axe.h"

Axe::Axe()
	: ItemWeapon("Axe", "A axe", 3.5f, 200, 25)
{
}

Axe::Axe(const std::string& name, const std::string& description, float weight, int value, int damage)
	: ItemWeapon(name, description, weight, value, damage)
{
}

Axe::~Axe()
{
}
