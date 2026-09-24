#pragma once
#include "Movement.h"
#include "Inventory.h"
#include <string>
#include <memory>
#include "Map.h"
#include "PathFinder.h"
#include <vector>

class Character : public Movement
{
public:
	Character();
	virtual ~Character();

	// Movement Interface Implementierung
	void moveUp() override;
	void moveDown() override;
	void moveLeft() override;
	void moveRight() override;

	int getX() const override;
	int getY() const override;
	void setPosition(int x, int y) override;

	// Character Eigenschaften
	const std::string& getName() const;
	void setName(const std::string& name);

	void setCurrentMap(std::shared_ptr<Map> map);


	float getStrength() const;
	void setStrength(float strength);

	// Tragegewicht (1 Stärke = +2 Gewicht)
	float getMaxCarryWeight() const;
	bool isOverWeight() const;
	// Passt das Item noch ins Tragegewicht, ohne überladen zu sein?
	bool canCarry(const ItemBase& item) const;

	// ---- Automatisches Laufen zum Exit ----
	// Berechnet mit A* den Weg von der aktuellen Position zum Exit und startet das Laufen.
	// Die Schritte selbst passieren in updateAutoWalk(), damit man die Bewegung sieht.
	// Gibt false zurück, wenn es keinen Weg gibt oder der Character überladen ist.
	bool autoWalk(float stepDelay = 0.25f);
	// Jeden Frame aufrufen: macht alle stepDelay Sekunden einen Schritt
	void updateAutoWalk(float deltaTime);
	void stopAutoWalk();
	bool isAutoWalking() const;

	// Inventar
	std::shared_ptr<Inventory<ItemBase, ItemEquippable>> getInventory() const;
	void pickUpItem();
	void changeInventorySlot(int offset);
	void equipItem();
	void dropItem();


private:
	// Gemeinsamer Bewegungscode für moveUp/Down/Left/Right und autoWalk.
	// Gibt false zurück, wenn das Ziel-Tile nicht begehbar ist.
	bool moveTo(int newX, int newY);

	// Hebt das Item auf dem aktuellen Tile automatisch auf (Aufgabe 2)
	// und rüstet es aus, wenn es einen besseren Stärkebonus gibt (Aufgabe 3)
	void autoPickUpItem();

	// Ersetzt das Schatz-Tile unter dem Character durch ein leeres Tile
	void clearTreasureTile();

	std::string name;
	int posx;
	int posy;
	std::shared_ptr<Map> currentMap;
	std::shared_ptr<Inventory<ItemBase, ItemEquippable>> m_inventory;

	std::vector<GridPosition> autoWalkPath; // geplanter Weg von autoWalk()
	std::size_t autoWalkIndex = 0;          // nächster Schritt in autoWalkPath
	float autoWalkStepDelay = 0.25f;        // Sekunden zwischen zwei Schritten
	float autoWalkTimer = 0.0f;
protected:
	float strength;
};
