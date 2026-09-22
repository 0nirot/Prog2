#include "ItemBase.h"

ItemBase::ItemBase()
	: name(""), description(""), weight(0.0f), value(0)
{
}

ItemBase::ItemBase(const std::string& name, const std::string& description, float weight, int value)
	: name(name), description(description), weight(weight), value(value)
{
}

ItemBase::~ItemBase()
{
}

const std::string& ItemBase::getName() const
{
	return name;
}

const std::string& ItemBase::getDescription() const
{
	return description;
}

float ItemBase::getWeight() const
{
	return weight;
}

int ItemBase::getValue() const
{
	return value;
}

void ItemBase::setName(const std::string& newName)
{
	name = newName;
}

void ItemBase::setDescription(const std::string& newDescription)
{
	description = newDescription;
}

void ItemBase::setWeight(float newWeight)
{
	weight = newWeight;
}

void ItemBase::setValue(int newValue)
{
	value = newValue;
}
