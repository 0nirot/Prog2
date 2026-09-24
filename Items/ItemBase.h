#pragma once
#include <memory>
#include <string>

class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase();

	// Polymorphe Kopie: erzeugt eine Kopie mit dem echten (dynamischen) Typ,
	// damit beim Kopieren über einen ItemBase-Zeiger kein Object Slicing passiert.
	// Jede Kindklasse muss diese Methode überschreiben.
	virtual std::unique_ptr<ItemBase> clone() const { return std::make_unique<ItemBase>(*this); }

	// Getter
	const std::string& getName() const;
	const std::string& getDescription() const;
	float getWeight() const;
	int getValue() const;


// Setter
	void setName(const std::string& name);
	void setDescription(const std::string& description);
	void setWeight(float weight);
	void setValue(int value);

protected:
	std::string name;
	std::string description;
	float weight;
	int value;
};
