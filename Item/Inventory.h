//
// Created by nova on 7/27/25.
// List ADT implementation for handling player or shop inventories
//

#ifndef INVENTORY_H
#define INVENTORY_H

#include "../ADTBaseClasses/List.h"

class Item;

class Inventory : public List<Item> {
public:
    enum class SortParameter {
        ID = 1,
        Value = 2,
        Type = 3,
        Effect = 4,
        Damage = 5,
        Defense = 6,
        Potency = 7,
        Duration = 8
    };

    enum class SortOrder {
        Ascending = 1,
        Descending = 2
    };

    void SortInventory(SortParameter parameter, SortOrder order);
    void PrintInventory();
    bool HasItemWithID(int id);
    Item* GetItemWithID(int id);
    Item* RemoveItemWithID(int id);
private:
    // Static helper functions for sorting
    static bool NotInCorrectOrder(Item* a, Item* b, SortParameter parameter, SortOrder order);
    static bool ShouldSwap(int valueA, int valueB, SortOrder order);
};



#endif //INVENTORY_H
