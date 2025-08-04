//
// Created by nova on 7/21/25.
//

#include "InventoryNode.h"

int InventoryNode::GetItemDamage() {
    auto* weapon = dynamic_cast<Weapon*>(item);
    if (weapon) {
        return weapon->GetDamage();
    }
    return 0;
}

int InventoryNode::GetItemDefense() {
    auto* armor = dynamic_cast<Armor*>(item);
    if (armor) {
        return armor->GetDefense();
    }
    return 0;
}

int InventoryNode::GetItemPotency() {
    auto* potion = dynamic_cast<Potion*>(item);
    if (potion) {
        return potion->GetPotency();
    }
    return 0;
}

int InventoryNode::GetItemDuration() {
    auto* potion = dynamic_cast<Potion*>(item);
    if (potion) {
        return potion->GetDuration();
    }
    return 0;
}