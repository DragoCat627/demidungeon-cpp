//
// Created by nova on 7/8/25.
//

#include <climits>

#include "Item.h"

int Item::nextId = 1;

Item::Item(int value, Effect effect, Type type)
    : value(value), effect(effect), type(type) {
    id = nextId++;
}


std::string Item::GetDamage() {
    return " ";
}

std::string Item::GetDefense() {
    return " ";
}

std::string Item::GetPotency() {
    return " ";
}

std::string Item::GetDuration() {
    return " ";
}

// For sorting, if an item doesn't actually have a value, then it needs to be pushed to the bottom of the list
int Item::GetDamage(Inventory::SortOrder sortOrder) {
    return (sortOrder == Inventory::SortOrder::Ascending) ? INT_MAX : INT_MIN;
}

int Item::GetDefense(Inventory::SortOrder sortOrder) {
    return (sortOrder == Inventory::SortOrder::Ascending) ? INT_MAX : INT_MIN;
}

int Item::GetPotency(Inventory::SortOrder sortOrder) {
    return (sortOrder == Inventory::SortOrder::Ascending) ? INT_MAX : INT_MIN;
}

int Item::GetDuration(Inventory::SortOrder sortOrder) {
    return (sortOrder == Inventory::SortOrder::Ascending) ? INT_MAX : INT_MIN;
}

std::string Item::GetTypeAsString() {
    switch (type) {
        case Type::None:
            return "None";
        case Type::Weapon:
            return "Weapon";
        case Type::Armor:
            return "Armor";
        case Type::Potion:
            return "Potion";
        default:
            return "None";
    }
}

std::string Item::GetEffectAsString() {
    switch (effect) {
        case Effect::None:
            return "None";
        case Effect::Fire:
            return "Fire";
        case Effect::Poison:
            return "Poison";
        default:
            return "None";
    }
}



