//
// Created by nova on 7/21/25.
// Potion item class, used during combat to apply a status effect
//

#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item {
    int potency;
    int duration;
public:
    explicit Potion(int value, int potency = 1, int duration = 1, Effect effect = Effect::None)
        : Item(value, effect, Type::Potion), potency(potency), duration(duration) {}

    int GetPotency(Inventory::SortOrder sortOrder) override {return potency;}
    int GetDuration(Inventory::SortOrder sortOrder) override {return duration;}
    std::string GetPotency() override {return std::to_string(potency);}
    std::string GetDuration() override {return std::to_string(duration);}
};



#endif //POTION_H
