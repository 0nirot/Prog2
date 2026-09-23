#pragma once

#include "Character.h"

class PlayerCharacter : public Character
{
public:
	explicit PlayerCharacter();
	~PlayerCharacter();

	int getStrength() const;
	void setStrength(int s);

	// Maximales Tragegewicht (1 Stärke = +2 Gewicht)
	float getMaxCarryWeight() const;

	// Aktuell getragenes Gewicht (Tasche + Ausrüstung)
	float getCurrentCarryWeight() const;

	// Prüft, ob zusätzliches Gewicht noch mitgeführt werden kann
	bool isOverWeight() const;

	// Versucht ein Item in die Tasche zu legen (prüft Gewichtslimit)
	// Gibt true zurück, wenn das Item erfolgreich gelegt wurde
	bool tryAddToBag(std::shared_ptr<ItemBase> item);

private:
	int strength;
};
