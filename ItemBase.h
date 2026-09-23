#pragma once
#include <string>

class ItemBase
{
public:
	ItemBase();
	explicit ItemBase(const std::string& name, const std::string& description, float weight, int value);
	virtual ~ItemBase();

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
