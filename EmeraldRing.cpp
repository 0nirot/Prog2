#include "EmeraldRing.h"

EmeraldRing::EmeraldRing()
	: ItemTrinket("Emerald Ring", "A beautiful ring adorned with a radiant emerald stone", 0.05f, 120, 8)
{
}

EmeraldRing::EmeraldRing(const std::string& name, const std::string& description, float weight, int value, int magicBonus)
	: ItemTrinket(name, description, weight, value, magicBonus)
{
}

EmeraldRing::~EmeraldRing()
{
}
