#pragma once
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include "Items\ItemEquippable.h"

// Beschreibt, welcher Item-Typ in einem Slot erlaubt ist.
// Der Typ-Check wird als Funktionszeiger gespeichert (type erasure),
// damit alle Slots im selben vector liegen können.
template<typename TBase>
struct SlotType
{
    bool (*accepts)(const TBase*);
    const char* name;
};

// Erzeugt einen Slot, der nur TAllowed (oder Kindklassen davon) akzeptiert
template<typename TAllowed, typename TBase = ItemEquippable>
SlotType<TBase> makeSlotType(const char* name = "")
{
    static_assert(std::is_base_of_v<TBase, TAllowed>, "TAllowed muss von TBase erben");

    return SlotType<TBase>{
        [](const TBase* item) { return dynamic_cast<const TAllowed*>(item) != nullptr; },
            name
    };
}

// Container, bei dem jeder Slot an einen bestimmten Item-Typ gebunden ist
template<typename T>
class EquipmentContainer
{
    static_assert(std::is_base_of_v<ItemEquippable, T>, "T muss von ItemEquippable erben");

public:
    using ItemPtr = std::shared_ptr<T>;

    // Das Layout legt bei der Instanziierung Anzahl UND Typ der Slots fest
    explicit EquipmentContainer(std::vector<SlotType<T>> layout)
        : m_slotTypes(std::move(layout))
        , m_slots(m_slotTypes.size())
    {
    }

    // Passt das Item in diesen Slot?
    bool accepts(std::size_t slot, const ItemPtr& item) const
    {
        return isValidSlot(slot) && item && m_slotTypes[slot].accepts(item.get());
    }

    // Setzt ein Item in einen bestimmten Slot.
    // Gibt false zurück, wenn der Slot ungültig ist oder der Typ nicht passt.
    // nullptr leert den Slot.
    bool setItem(std::size_t slot, ItemPtr item)
    {
        if (!isValidSlot(slot))
            return false;
        if (item && !m_slotTypes[slot].accepts(item.get()))
            return false;

        m_slots[slot] = std::move(item);
        return true;
    }

    ItemPtr getItem(std::size_t slot) const
    {
        return isValidSlot(slot) ? m_slots[slot] : nullptr;
    }

    // Typisierter Zugriff: getItemAs<ItemWeapon>(0)
    template<typename TAs>
    std::shared_ptr<TAs> getItemAs(std::size_t slot) const
    {
        return std::dynamic_pointer_cast<TAs>(getItem(slot));
    }

    // Legt das Item in den ersten freien, passenden Slot.
    // Gibt den Slotindex zurück, oder -1 wenn keiner frei/passend ist.
    int addItem(ItemPtr item)
    {
        if (!item)
            return -1;

        for (std::size_t i = 0; i < m_slots.size(); ++i)
        {
            if (!m_slots[i] && m_slotTypes[i].accepts(item.get()))
            {
                m_slots[i] = std::move(item);
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    ItemPtr removeItem(std::size_t slot)
    {
        if (!isValidSlot(slot))
            return nullptr;

        return std::exchange(m_slots[slot], nullptr);
    }

    const char* getSlotTypeName(std::size_t slot) const
    {
        return isValidSlot(slot) ? m_slotTypes[slot].name : "";
    }

    std::size_t getSlotCount() const { return m_slots.size(); }
    bool isValidSlot(std::size_t slot) const { return slot < m_slots.size(); }

private:
    std::vector<SlotType<T>> m_slotTypes; // fix nach dem Konstruktor
    std::vector<ItemPtr> m_slots;
};