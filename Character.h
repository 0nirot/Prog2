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

	void moveUp() override;
	void moveDown() override;
	void moveLeft() override;
	void moveRight() override;

	int getX() const override;
	int getY() const override;
	void setPosition(int x, int y) override;

	const std::string& getName() const;
	void setName(const std::string& name);

	void setCurrentMap(std::shared_ptr<Map> map);


	float getStrength() const;
	void setStrength(float strength);

	float getMaxCarryWeight() const;
	bool isOverWeight() const;
	bool canCarry(std::shared_ptr<ItemBase>& item) const;

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
	bool moveTo(int newX, int newY);

	void autoPickUpItem();

	void clearTreasureTile();

	std::string name;
	int posx;
	int posy;
	std::shared_ptr<Map> currentMap;
	std::shared_ptr<Inventory<ItemBase, ItemEquippable>> m_inventory;

	std::vector<GridPosition> autoWalkPath;
	std::size_t autoWalkIndex = 0;          
	float autoWalkStepDelay = 0.25f;        
	float autoWalkTimer = 0.0f;
protected:
	float strength;
};
