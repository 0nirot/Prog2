#pragma once
#include <memory>
#include <vector>

#include "Items\ItemBase.h"


void sortByWeight(std::vector<std::shared_ptr<ItemBase>>& items);

void sortByName(std::vector<std::shared_ptr<ItemBase>>& items);

void sortByValue(std::vector<std::shared_ptr<ItemBase>>& items);
