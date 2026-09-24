#pragma once

#include "Character.h"

class PlayerCharacter : public Character
{
public:
	explicit PlayerCharacter();
	~PlayerCharacter();

	bool tryAddToBag(std::shared_ptr<ItemBase> item);
};
