#pragma once
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include "Items\ItemBase.h"

// Generischer Container für Items. T muss ItemBase oder eine Kindklasse davon sein.
template<typename T>
class ItemContainer
{
    static_assert(std::is_base_of_v<ItemBase, T>, "T muss von ItemBase erben");

public:
    using ItemPtr = std::shared_ptr<T>;

    // Anzahl der Slots wird bei der Instanziierung festgelegt und ist danach fix
    explicit ItemContainer(std::size_t slotCount)
        : m_slots(slotCount)
    {
    }

    // Setzt ein Item in einen bestimmten Slot (überschreibt vorhandenes Item).
    // nullptr leert den Slot. Gibt false zurück, wenn der Slot ungültig ist.
    bool setItem(std::size_t slot, ItemPtr item)
    {
        if (!isValidSlot(slot))
            return false;

        m_slots[slot] = std::move(item);
        return true;
    }

    // Gibt das Item im Slot zurück, oder nullptr wenn leer/ungültig
    ItemPtr getItem(std::size_t slot) const
    {
        return isValidSlot(slot) ? m_slots[slot] : nullptr;
    }

    // Legt das Item in den ersten freien Slot.
    // Gibt den Slotindex zurück, oder -1 wenn der Container voll ist.
    int addItem(ItemPtr item)
    {
        if (!item)
            return -1;

        for (std::size_t i = 0; i < m_slots.size(); ++i)
        {
            if (!m_slots[i])
            {
                m_slots[i] = std::move(item);
                return static_cast<int>(i);
            }
        }
        return -1; // maximale Anzahl erreicht
    }

    // Entfernt das Item aus dem Slot und gibt es zurück
    ItemPtr removeItem(std::size_t slot)
    {
        if (!isValidSlot(slot))
            return nullptr;

        return std::exchange(m_slots[slot], nullptr);
    }

    std::size_t getSlotCount() const { return m_slots.size(); }

    std::size_t getItemCount() const
    {
        std::size_t count = 0;
        for (const auto& item : m_slots)
            if (item)
                ++count;
        return count;
    }

    bool isFull() const { return getItemCount() == getSlotCount(); }
    bool isValidSlot(std::size_t slot) const { return slot < m_slots.size(); }

private:
    // Wird nach dem Konstruktor nie vergrößert -> Slotanzahl kann nicht überschritten werden
    std::vector<ItemPtr> m_slots;
};