#pragma once

#include "Character.h"

class PlayerCharacter : public Character
{
public:
	explicit PlayerCharacter();
	~PlayerCharacter();

	// Versucht ein Item in die Tasche zu legen (prüft Gewichtslimit)
	// Gibt true zurück, wenn das Item erfolgreich gelegt wurde
	bool tryAddToBag(std::shared_ptr<ItemBase> item);
};
