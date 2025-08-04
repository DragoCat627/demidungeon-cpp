//
// Created by nova on 7/21/25.
//

#ifndef INVENTORYNODE_H
#define INVENTORYNODE_H

#include "../Item/Item.h"
#include "../Item/Potion.h"
#include "../Item/Armor.h"
#include "../Item/Weapon.h"
#include <string>

class InventoryNode {
    InventoryNode* next;
    InventoryNode* prev;
    Item* item;

    explicit InventoryNode(Item* item, InventoryNode* nex = nullptr, InventoryNode* pre = nullptr)
        : next(nex), prev(pre), item(item) {}

    void SetNext(InventoryNode* next) {this->next = next;}
    void SetPrev(InventoryNode* prev) {this->prev = prev;}

    InventoryNode* GetNext() const {return next;}
    InventoryNode* GetPrev() const {return prev;}

    void SetItem(Item* item) {this->item = item;}
    Item* GetItem() const {return item;}

    int GetItemValue() {return item->GetValue();}
    std::string GetItemEffect() {return item->GetEffect();}
    int GetItemDamage();
    int GetItemDefense();
    int GetItemPotency();
    int GetItemDuration();
    int GetItemID() {return item->GetID();}

};



#endif //INVENTORYNODE_H
