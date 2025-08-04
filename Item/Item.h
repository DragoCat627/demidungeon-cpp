//
// Created by nova on 7/8/25.
// Base class for all item objects
//

#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "Inventory.h"

class Item {
protected:
    static int nextId;
    int id;

    int value = 0;
public:
    enum class Type {
        None = 0,
        Weapon = 1,
        Armor = 2,
        Potion = 3
    };

    enum class Effect {
        None = 0,
        Fire = 1,
        Poison = 2,
        Regeneration = 3,
    };
    Type type = Type::None;
    Effect effect = Effect::None;

    virtual ~Item() = default;
    explicit Item(int value = 0, Effect effect = Effect::None, Type type = Type::None);

    // Equality operator 5/3, returns true if the IDs are identical
    bool operator==(const Item &other) const {return id == other.GetID();}

    int GetValue() const {return value;}
    Type GetType() const {return type;}
    Effect GetEffect() const {return effect;}
    int GetID() const {return id;}

    // Unless these are overridden in a base class, they return a null value
    // an empty string for these
    virtual std::string GetDamage();
    virtual std::string GetDefense();
    virtual std::string GetPotency();
    virtual std::string GetDuration();
    // Either INT_MAX or INT_MIN for these, depending on the sort order
    virtual int GetDamage(Inventory::SortOrder sortOrder);
    virtual int GetDefense(Inventory::SortOrder sortOrder);
    virtual int GetPotency(Inventory::SortOrder sortOrder);
    virtual int GetDuration(Inventory::SortOrder sortOrder);

    std::string GetTypeAsString();
    std::string GetEffectAsString();

    bool IsEmpty() const {return id == 0;}
};



#endif //ITEM_H
