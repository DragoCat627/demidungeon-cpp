//
// Created by nova on 7/8/25.
// Entity base class for the player and enemy subclasses.
//
//

#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "../StatusEffects/StatusEffect.h"
#include "../StatusEffects/StatusEffectQueue.h"

class Game;
class Menu;
class StatusEffect;

class Entity {
protected:
    int health;
    int defense;

    int entityID;
    static int nextID;

    StatusEffectQueue* statusEffects = new StatusEffectQueue();
public:
    enum class Type {
        None = 0,
        Player = 1,
        Enemy = 2,
    };

    Type type;

    explicit Entity(int heath = 100, int defense = 5, Type type = Type::None, int id = nextID++)
        : health(heath), defense(defense), entityID(id), type(type) {}
    virtual ~Entity() = default;

    virtual void TakeTurn(Menu* menu, Game* game) = 0;

    // Equality operator overload 3/3, returns true if the IDs are identical
    bool operator==(const Entity* other) const {return entityID == other->entityID;}
    // Not Equal operator overload 4/3, returns false if the IDs are identical
    bool operator!=(const Entity* other) const {return entityID != other->entityID;}

    void ApplyStatusEffect(StatusEffect* effect) {statusEffects->Enqueue(effect);}
    void TickStatusEffects(Game* game);

    int GetHealth() const {return health;}
    int GetDefense() const {return defense;}
    StatusEffectQueue* GetStatusEffectQueue() const {return statusEffects;}
    virtual std::string GetEntityName() = 0;

    void TakeDamage(int amount, Game* game, bool ignoreDefense = false);
    void ReduceDefense(int amount) {defense -= amount;}
    virtual void Heal(int amount) {health += amount;}
    void IncreaseDefense(int amount) {defense += amount;}

    int GetID() const {return entityID;}

    bool IsAlive() const {return health > 0;}
    virtual bool IsPlayer() const = 0;
};

#endif //ENTITY_H
