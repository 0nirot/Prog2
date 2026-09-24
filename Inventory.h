#pragma once
#include <algorithm>
#include <cstddef>
#include <memory>
#include <type_traits>
#include <vector>

#include "Items\ItemBase.h"
#include "Items\ItemEquippable.h"
#include "ItemContainer.h"
#include "EquipmentContainer.h"
#include "SortAlgorithms.h"

class Character;

template<typename TItem = ItemBase, typename TEquippable = ItemEquippable, typename TOwner = Character>
class Inventory
{

    static_assert(std::is_base_of_v<TItem, TEquippable>, "TEquippable muss in TItem passen");

public:

    Inventory(std::size_t bagSlots, std::vector<SlotType<TEquippable>> layout, TOwner* owner = nullptr)
        : m_bag(bagSlots)
        , m_equipment(std::move(layout))
        , m_owner(owner)
    {
    }

    bool setBagItem(std::size_t slot, std::shared_ptr<TItem> item) { return m_bag.setItem(slot, std::move(item)); }
    std::shared_ptr<TItem> getBagItem(std::size_t slot) const { return m_bag.getItem(slot); }
    int addBagItem(std::shared_ptr<TItem> item) { return m_bag.addItem(std::move(item)); }
    std::shared_ptr<TItem> removeBagItem(std::size_t slot) { return m_bag.removeItem(slot); }

    std::shared_ptr<TEquippable> getEquipmentItem(std::size_t slot) const { return m_equipment.getItem(slot); }

    template<typename TAs>
    std::shared_ptr<TAs> getEquipmentItemAs(std::size_t slot) const { return m_equipment.template getItemAs<TAs>(slot); }

    bool equip(std::size_t bagSlot)
    {
        auto item = std::dynamic_pointer_cast<TEquippable>(m_bag.getItem(bagSlot));
        if (!item)
            return false;

        const int equipSlot = m_equipment.findSlotFor(item);
        if (equipSlot < 0)
            return false;

        auto previous = m_equipment.getItem(equipSlot);
        m_equipment.setItem(equipSlot, item);
        m_bag.setItem(bagSlot, previous);

        if (previous)
            onUnequipped(previous);
        onEquipped(item);
        return true;
    }

    bool isBetterThanEquipped(const std::shared_ptr<TEquippable>& item) const
    {
        if (!item)
            return false;

        const int equipSlot = m_equipment.findSlotFor(item);
        if (equipSlot < 0)
            return false;

        auto current = m_equipment.getItem(equipSlot);
        const float currentBonus = current ? current->getStrengthBonus() : 0.0f;
        return item->getStrengthBonus() > currentBonus;
    }

    bool equipSelectedItem() { return equip(m_selectedSlotIndex); }

    bool unequip(std::size_t equipSlot)
    {
        auto item = m_equipment.getItem(equipSlot);
        if (!item || m_bag.addItem(item) < 0)
            return false;

        m_equipment.setItem(equipSlot, nullptr);
        onUnequipped(item);
        return true;
    }

    const ItemContainer<TItem>& getBag() const { return m_bag; }
    const EquipmentContainer<TEquippable>& getEquipment() const { return m_equipment; }

    float getTotalWeight() const
    {
        return sumWeight(m_bag) + sumWeight(m_equipment);
    }

    std::size_t getSelectedSlotIndex() const { return m_selectedSlotIndex; }

    void selectNextSlot(int offset)
    {
        const int slotCount = static_cast<int>(m_bag.getSlotCount());
        if (slotCount <= 0)
            return;

        const int next = static_cast<int>(m_selectedSlotIndex) + offset;
        m_selectedSlotIndex = static_cast<std::size_t>(std::clamp(next, 0, slotCount - 1));
    }


    void sortBagByWeight()
    {
		printf("Sorting bag by weight...\n");
        auto items = takeBagItems();
        sortByWeight(items);
        putBagItems(items);
    }

    void sortBagByName()
    {
        printf("Sorting bag by name...\n");
        auto items = takeBagItems();
        sortByName(items);
        putBagItems(items);
    }

    void sortBagByValue()
    {
		printf("Sorting bag by value...\n");
        auto items = takeBagItems();
        sortByValue(items);
        putBagItems(items);
    }

private:
    std::vector<std::shared_ptr<ItemBase>> takeBagItems()
    {
        std::vector<std::shared_ptr<ItemBase>> items;
        for (std::size_t i = 0; i < m_bag.getSlotCount(); ++i)
        {
            if (auto item = m_bag.removeItem(i))
                items.push_back(item);
        }
        return items;
    }

    void putBagItems(const std::vector<std::shared_ptr<ItemBase>>& items)
    {
        for (std::size_t i = 0; i < items.size(); ++i)
            m_bag.setItem(i, std::static_pointer_cast<TItem>(items[i]));
    }

    void onEquipped(const std::shared_ptr<TEquippable>& item)
    {
        item->setEquipped(true);
        changeOwnerStrength(item->getStrengthBonus());
    }

    void onUnequipped(const std::shared_ptr<TEquippable>& item)
    {
        item->setEquipped(false);
        changeOwnerStrength(-item->getStrengthBonus());
    }

    void changeOwnerStrength(float delta)
    {
        if (m_owner)
            m_owner->setStrength(m_owner->getStrength() + delta);
    }

    template<typename TContainer>
    static float sumWeight(const TContainer& container)
    {
        float total = 0.0f;
        for (std::size_t i = 0; i < container.getSlotCount(); ++i)
        {
            if (auto item = container.getItem(i))
                total += item->getWeight();
        }
        return total;
    }

    ItemContainer<TItem> m_bag;
    EquipmentContainer<TEquippable> m_equipment;
    std::size_t m_selectedSlotIndex = 0;

    TOwner* m_owner;
};
