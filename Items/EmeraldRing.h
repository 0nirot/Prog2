#pragma once
#include "ItemTrinket.h"

class EmeraldRing : public ItemTrinket
{
public:
	EmeraldRing();
	~EmeraldRing();

	std::unique_ptr<ItemBase> clone() const override { return std::make_unique<EmeraldRing>(*this); }
};
