#include "Stick.h"

Stick::Stick()
	: ItemBase("Stick", "A simple wooden stick found in the forest", 0.5f, 5)
{
}

Stick::Stick(const std::string& name, const std::string& description, float weight, int value)
	: ItemBase(name, description, weight, value)
{
}

Stick::~Stick()
{
}
