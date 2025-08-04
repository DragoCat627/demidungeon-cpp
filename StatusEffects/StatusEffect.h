//
// Created by nova on 7/8/25.
// Status effect objects to be stored on a given entity during combat.
//

#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H
#include <string>

class Game;
class Entity;

class StatusEffect {
protected:
    int potency;
    int duration;
    Entity* target;
public:
    virtual ~StatusEffect() = default;

    enum class Type {
        OnFire,
        Poisoned,
        Regeneration
    };

    Type type;

    StatusEffect(int potency, int duration, Entity* target)
        : potency(potency), duration(duration), target(target) {}


    int GetPotency() const {return potency;}
    int GetDuration() const {return duration;}
    virtual Type GetType() const = 0;
    virtual std::string GetTypeAsString() {return "Unknown";}

    bool operator==(const StatusEffect& other) const {return GetType() == other.GetType();}

    // Polymorphic function to handle the ticking of the status effect,
    // depending on the effect damage will need to be done, or defense lowered
    void virtual Tick(Game* game) = 0;

    void DecrementDuration() {duration--;};
};



#endif //STATUSEFFECT_H
