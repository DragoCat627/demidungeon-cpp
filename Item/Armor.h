//
// Created by nova on 7/21/25.
// Class for armor items
//

#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"

class Armor : public Item {
    int defense;
public:
    explicit Armor(int value = 0, int defense = 0, Effect effect = Effect::None)
        : Item(value, Effect::None, Type::Armor), defense(defense) {}

    int GetDefense(Inventory::SortOrder sortOrder) override {return defense;}
    std::string GetDefense() override {return std::to_string(defense);}
};




#endif //ARMOR_H
