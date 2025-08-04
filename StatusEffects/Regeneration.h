//
// Created by nova on 7/30/25.
// Regeneration status effect, increases the entity's health for each tick
//

#ifndef REGENERATION_H
#define REGENERATION_H
#include "StatusEffect.h"


class Regeneration : public StatusEffect {
public:
    Regeneration(int potency, int duration, Entity* target)
        : StatusEffect(potency, duration, target) {}
    ~Regeneration() override;
    Type GetType() const override {return Type::Regeneration;}
    std::string GetTypeAsString() override {return "Regeneration";}
    void Tick(Game* game) override;
};



#endif //REGENERATION_H
