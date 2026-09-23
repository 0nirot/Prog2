#include "Apple.h"

Apple::Apple()
	: ItemBase("Apple", "A fresh and juicy red apple", 0.2f, 10)
{
}

Apple::Apple(const std::string& name, const std::string& description, float weight, int value)
	: ItemBase(name, description, weight, value)
{
}

Apple::~Apple()
{
}
