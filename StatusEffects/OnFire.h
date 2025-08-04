//
// Created by nova on 7/21/25.
// Fire status effect, makes the entity take damage for every tick
//

#ifndef ONFIRE_H
#define ONFIRE_H

#include "StatusEffect.h"

class Game;

class OnFire : public StatusEffect {
public:
    OnFire(int potency, int duration, Entity* target)
        : StatusEffect(potency, duration, target) {}
    ~OnFire() override;
    Type GetType() const override {return Type::OnFire;}
    std::string GetTypeAsString() override {return "Fire";}
    void Tick(Game* game) override;
};




#endif //ONFIRE_H
