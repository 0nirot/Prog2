#include "Torch.h"

Torch::Torch()
	: ItemBase("Torch", "A wooden torch with a burning flame that illuminates the darkness", 0.8f, 15)
{
}

Torch::Torch(const std::string& name, const std::string& description, float weight, int value)
	: ItemBase(name, description, weight, value)
{
}

Torch::~Torch()
{
}
