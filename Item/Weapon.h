//
// Created by nova on 7/21/25.
// Weapon item class, modifies the player's defense, and if it's a rare variant, applies a weak status effect upon attacking
//

#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item {
    int damage;

public:
    explicit Weapon(int value = 0, int damage = 0, Effect effect = Effect::None)
        : Item(value, effect, Type::Weapon), damage(damage) {}

    int GetDamage(Inventory::SortOrder sortOrder) override {return damage;}
    std::string GetDamage() override {return std::to_string(damage);}
};



#endif //WEAPON_H
