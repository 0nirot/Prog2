#pragma once
#include <memory>
#include <vector>

#include "Items\ItemBase.h"

// Einfache Sortierfunktionen für eine Liste von Items.
// Alle sortieren aufsteigend. Die Liste darf keine nullptr enthalten.

// Selection Sort (Linear Sort): sortiert nach Gewicht
void sortByWeight(std::vector<std::shared_ptr<ItemBase>>& items);

// Bubble Sort: sortiert nach Name (A-Z)
void sortByName(std::vector<std::shared_ptr<ItemBase>>& items);

// Merge Sort: sortiert nach Wert
void sortByValue(std::vector<std::shared_ptr<ItemBase>>& items);
