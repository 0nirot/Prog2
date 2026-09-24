#pragma once
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include "Items\ItemEquippable.h"

template<typename TBase>
struct SlotType
{
    bool (*accepts)(const TBase*);
    const char* name;
};

template<typename TAllowed, typename TBase = ItemEquippable>
SlotType<TBase> makeSlotType(const char* name = "")
{
    static_assert(std::is_base_of_v<TBase, TAllowed>, "TAllowed muss von TBase erben");

    return SlotType<TBase>{
        [](const TBase* item) { return dynamic_cast<const TAllowed*>(item) != nullptr; },
            name
    };
}

template<typename T>
class EquipmentContainer
{
    static_assert(std::is_base_of_v<ItemEquippable, T>, "T muss von ItemEquippable erben");

public:
    using ItemPtr = std::shared_ptr<T>;

    explicit EquipmentContainer(std::vector<SlotType<T>> layout)
        : m_slotTypes(std::move(layout))
        , m_slots(m_slotTypes.size())
    {
    }

    bool accepts(std::size_t slot, const ItemPtr& item) const
    {
        return isValidSlot(slot) && item && m_slotTypes[slot].accepts(item.get());
    }

    int findSlotFor(const ItemPtr& item) const
    {
        int firstMatch = -1;
        for (std::size_t i = 0; i < m_slots.size(); ++i)
        {
            if (!accepts(i, item))
                continue;
            if (!m_slots[i])
                return static_cast<int>(i);
            if (firstMatch < 0)
                firstMatch = static_cast<int>(i);
        }
        return firstMatch;
    }

    bool setItem(std::size_t slot, ItemPtr item)
    {
        if (!isValidSlot(slot) || (item && !accepts(slot, item)))
            return false;

        m_slots[slot] = std::move(item);
        return true;
    }

    ItemPtr getItem(std::size_t slot) const
    {
        return isValidSlot(slot) ? m_slots[slot] : nullptr;
    }

    template<typename TAs>
    std::shared_ptr<TAs> getItemAs(std::size_t slot) const
    {
        return std::dynamic_pointer_cast<TAs>(getItem(slot));
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
    std::vector<SlotType<T>> m_slotTypes;
    std::vector<ItemPtr> m_slots;
};