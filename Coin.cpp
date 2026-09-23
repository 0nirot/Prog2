#include "Coin.h"

Coin::Coin()
	: ItemBase("Coin", "A golden coin with ancient engravings", 0.01f, 25)
{
}

Coin::Coin(const std::string& name, const std::string& description, float weight, int value)
	: ItemBase(name, description, weight, value)
{
}

Coin::~Coin()
{
}
