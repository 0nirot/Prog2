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

// Nur Forward-Declaration: Character.h inkludiert Inventory.h,
// ein #include "Character.h" hier wäre zirkulär.
class Character;

// TItem       -> Typ für den allgemeinen Container (Tasche), Standard: ItemBase
// TEquippable -> Basistyp für den Ausrüstungs-Container, Standard: ItemEquippable
// TOwner      -> Besitzer des Inventars, bekommt die Stärkeboni der Ausrüstung.
//                Muss getStrength()/setStrength(float) anbieten. Standard: Character
template<typename TItem = ItemBase, typename TEquippable = ItemEquippable, typename TOwner = Character>
class Inventory
{
    // Ausgerüstete Items wandern beim Tauschen in die Tasche zurück,
    // deshalb muss ein TEquippable immer in einen TItem-Slot passen.
    // (Die übrigen Typ-Checks machen ItemContainer/EquipmentContainer selbst.)
    static_assert(std::is_base_of_v<TItem, TEquippable>, "TEquippable muss in TItem passen");

public:
    // bagSlots  -> Anzahl der Slots der Tasche
    // layout    -> Anzahl UND erlaubter Typ jedes Ausrüstungsslots
    // owner     -> nicht-besitzender Zeiger auf den Besitzer (darf nullptr sein)
    Inventory(std::size_t bagSlots, std::vector<SlotType<TEquippable>> layout, TOwner* owner = nullptr)
        : m_bag(bagSlots)
        , m_equipment(std::move(layout))
        , m_owner(owner)
    {
    }

    // ---- Tasche (kann alles halten) ----
    bool setBagItem(std::size_t slot, std::shared_ptr<TItem> item) { return m_bag.setItem(slot, std::move(item)); }
    std::shared_ptr<TItem> getBagItem(std::size_t slot) const { return m_bag.getItem(slot); }
    int addBagItem(std::shared_ptr<TItem> item) { return m_bag.addItem(std::move(item)); }
    std::shared_ptr<TItem> removeBagItem(std::size_t slot) { return m_bag.removeItem(slot); }

    // ---- Ausrüstung (nur lesend; Änderungen laufen über equip/unequip) ----
    std::shared_ptr<TEquippable> getEquipmentItem(std::size_t slot) const { return m_equipment.getItem(slot); }

    template<typename TAs>
    std::shared_ptr<TAs> getEquipmentItemAs(std::size_t slot) const { return m_equipment.template getItemAs<TAs>(slot); }

    // Rüstet das Item aus dem Taschenslot aus.
    // Der passende Ausrüstungsslot wird automatisch anhand des Item-Typs bestimmt.
    // Liegt dort bereits ein Item, wird getauscht: das alte Item landet genau
    // in dem Taschenslot, aus dem das neue Item kam.
    // Gibt false zurück, wenn das Item nicht ausrüstbar ist oder kein Slot passt.
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
        m_bag.setItem(bagSlot, previous); // nullptr, falls der Slot leer war -> Taschenslot wird frei

        // Erst den Bonus des alten Items abziehen, dann den des neuen addieren
        if (previous)
            onUnequipped(previous);
        onEquipped(item);
        return true;
    }

    // Prüft, ob das Item in seinem Ausrüstungsslot einen höheren Stärkebonus
    // geben würde als das Item, das dort gerade ausgerüstet ist.
    // Ist der Slot leer, zählt der aktuelle Bonus als 0.
    bool isBetterThanEquipped(const std::shared_ptr<TEquippable>& item) const
    {
        if (!item)
            return false;

        const int equipSlot = m_equipment.findSlotFor(item);
        if (equipSlot < 0)
            return false; // es gibt keinen Slot für diesen Typ

        auto current = m_equipment.getItem(equipSlot);
        const float currentBonus = current ? current->getStrengthBonus() : 0.0f;
        return item->getStrengthBonus() > currentBonus;
    }

    // Rüstet das aktuell ausgewählte Taschen-Item aus
    bool equipSelectedItem() { return equip(m_selectedSlotIndex); }

    // Verschiebt ein ausgerüstetes Item zurück in die Tasche (falls Platz ist)
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

    // ---- Auswahl in der Tasche ----
    std::size_t getSelectedSlotIndex() const { return m_selectedSlotIndex; }

    // Verschiebt die Auswahl um offset Slots (z.B. -1 / +1), begrenzt auf gültige Slots
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

    // Legt die Items der Reihe nach ab Slot 0 zurück in die Tasche
    void putBagItems(const std::vector<std::shared_ptr<ItemBase>>& items)
    {
        for (std::size_t i = 0; i < items.size(); ++i)
            m_bag.setItem(i, std::static_pointer_cast<TItem>(items[i]));
    }

    // Zentrale Stellen für alles, was beim (Ab-)Legen eines Items passiert.
    // So kann equip/unequip nie vergessen, Flag UND Bonus zu setzen.
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

    // Summiert das Gewicht aller belegten Slots eines beliebigen Containers
    // (funktioniert für ItemContainer und EquipmentContainer gleichermaßen)
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

    // Nicht-besitzend: Der Owner besitzt das Inventar, nicht umgekehrt.
    // Ein shared_ptr hier würde einen Zyklus (Owner <-> Inventar) erzeugen
    // bzw. versuchen, ein Stack-Objekt zu löschen.
    TOwner* m_owner;
};
