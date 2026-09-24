#include "SortAlgorithms.h"
#include <utility>

// ---------------------------------------------------------------------------
// Selection Sort nach Gewicht
// Sucht im unsortierten Rest das leichteste Item und tauscht es nach vorne.
// ---------------------------------------------------------------------------
void sortByWeight(std::vector<std::shared_ptr<ItemBase>>& items)
{
    for (size_t i = 0; i + 1 < items.size(); ++i)
    {
        size_t minIndex = i;
        for (size_t j = i + 1; j < items.size(); ++j)
        {
            if (items[j]->getWeight() < items[minIndex]->getWeight())
                minIndex = j;
        }
        std::swap(items[i], items[minIndex]);
    }
}

// ---------------------------------------------------------------------------
// Bubble Sort nach Name
// Vertauscht benachbarte Items, solange sie falsch herum stehen.
// Bricht ab, wenn ein Durchlauf ohne Tausch war.
// ---------------------------------------------------------------------------
void sortByName(std::vector<std::shared_ptr<ItemBase>>& items)
{
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (size_t i = 0; i + 1 < items.size(); ++i)
        {
            if (items[i]->getName() > items[i + 1]->getName())
            {
                std::swap(items[i], items[i + 1]);
                swapped = true;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// Merge Sort nach Wert
// Teilt die Liste in zwei Hälften, sortiert beide rekursiv
// und fügt sie danach sortiert wieder zusammen.
// ---------------------------------------------------------------------------
void sortByValue(std::vector<std::shared_ptr<ItemBase>>& items)
{
    if (items.size() < 2)
        return;

    // Aufteilen
    size_t mid = items.size() / 2;
    std::vector<std::shared_ptr<ItemBase>> left(items.begin(), items.begin() + mid);
    std::vector<std::shared_ptr<ItemBase>> right(items.begin() + mid, items.end());

    // Beide Hälften sortieren
    sortByValue(left);
    sortByValue(right);

    // Zusammenfügen: immer das kleinere vordere Element übernehmen
    size_t l = 0;
    size_t r = 0;
    size_t out = 0;
    while (l < left.size() && r < right.size())
    {
        if (left[l]->getValue() <= right[r]->getValue())
            items[out++] = left[l++];
        else
            items[out++] = right[r++];
    }
    while (l < left.size())
        items[out++] = left[l++];
    while (r < right.size())
        items[out++] = right[r++];
}
