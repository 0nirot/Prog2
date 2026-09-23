#pragma once
#include <cstddef>
#include <memory>
#include <type_traits>
#include <vector>

#include "Items\ItemBase.h"
#include "Items\ItemEquippable.h"
#include "ItemContainer.h"
#include "EquipmentContainer.h"

// TItem       -> Typ für den allgemeinen Container (Tasche), Standard: ItemBase
// TEquippable -> Basistyp für den Ausrüstungs-Container, Standard: ItemEquippable
template<typename TItem = ItemBase, typename TEquippable = ItemEquippable>
class Inventory
{
    static_assert(std::is_base_of_v<ItemBase, TItem>, "TItem muss von ItemBase erben");
    static_assert(std::is_base_of_v<ItemEquippable, TEquippable>, "TEquippable muss von ItemEquippable erben");
    static_assert(std::is_base_of_v<TItem, TEquippable>, "TEquippable muss in TItem passen");

public:
    // bagSlots  -> Anzahl der Slots der Tasche
    // layout    -> Anzahl UND erlaubter Typ jedes Ausrüstungsslots
    Inventory(std::size_t bagSlots, std::vector<SlotType<TEquippable>> layout)
        : m_bag(bagSlots)
        , m_equipment(std::move(layout))
    {
    }

    // ---- Tasche (kann alles halten) ----
    bool setBagItem(std::size_t slot, std::shared_ptr<TItem> item) { return m_bag.setItem(slot, std::move(item)); }
    std::shared_ptr<TItem> getBagItem(std::size_t slot) const { return m_bag.getItem(slot); }
    int addBagItem(std::shared_ptr<TItem> item) { return m_bag.addItem(std::move(item)); }
    std::shared_ptr<TItem> removeBagItem(std::size_t slot) { return m_bag.removeItem(slot); }

    // ---- Ausrüstung (pro Slot nur ein bestimmter Typ) ----
    bool setEquipmentItem(std::size_t slot, std::shared_ptr<TEquippable> item) { return m_equipment.setItem(slot, std::move(item)); }
    std::shared_ptr<TEquippable> getEquipmentItem(std::size_t slot) const { return m_equipment.getItem(slot); }

    template<typename TAs>
    std::shared_ptr<TAs> getEquipmentItemAs(std::size_t slot) const { return m_equipment.template getItemAs<TAs>(slot); }

    // Verschiebt ein Item aus der Tasche in einen Ausrüstungsslot.
    // Schlägt fehl, wenn das Item nicht equippable ist oder nicht zum Slottyp passt.
    // Ein bereits ausgerüstetes Item wandert in die Tasche zurück.
    bool equip(std::size_t bagSlot, std::size_t equipSlot)
    {
        auto equippable = std::dynamic_pointer_cast<TEquippable>(m_bag.getItem(bagSlot));
        if (!m_equipment.accepts(equipSlot, equippable))
            return false;

        auto previous = m_equipment.getItem(equipSlot);
        m_equipment.setItem(equipSlot, equippable);
        m_bag.setItem(bagSlot, previous);
        return true;
    }

    // Verschiebt ein ausgerüstetes Item zurück in die Tasche (falls Platz ist)
    bool unequip(std::size_t equipSlot)
    {
        auto item = m_equipment.getItem(equipSlot);
        if (!item || m_bag.addItem(item) < 0)
            return false;

        m_equipment.setItem(equipSlot, nullptr);
        return true;
    }

    const ItemContainer<TItem>& getBag() const { return m_bag; }
    const EquipmentContainer<TEquippable>& getEquipment() const { return m_equipment; }

	float getTotalWeight() const
	{
		float total = 0.0f;
		for (std::size_t i = 0; i < m_bag.getSlotCount(); ++i)
		{
			auto item = m_bag.getItem(i);
			if (item)
				total += item->getWeight();
		}
		for (std::size_t i = 0; i < m_equipment.getSlotCount(); ++i)
		{
			auto item = m_equipment.getItem(i);
			if (item)
				total += item->getWeight();
		}
		return total;
	}

private:
    ItemContainer<TItem> m_bag;
    EquipmentContainer<TEquippable> m_equipment;
};