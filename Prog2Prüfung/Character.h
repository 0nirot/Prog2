#pragma once
#include "Movement.h"
#include "Inventory.h"
#include <string>
#include <memory>

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

	int getHealth() const;
	void setHealth(int health);

	int getMaxHealth() const;
	void setMaxHealth(int maxHealth);

	// Schaden nehmen
	void takeDamage(int damage);

	// Heilen
	void heal(int amount);

	// Inventar
	std::shared_ptr<Inventory<ItemBase, ItemEquippable>> getInventory() const;

private:
	std::string name;
	int posx;
	int posy;
	int health;
	int maxHealth;
	std::shared_ptr<Inventory<ItemBase, ItemEquippable>> inventory;
};
