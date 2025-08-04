//
// Created by nova on 7/25/25.
// Poison status effect, temporarily lowers the entities defense for the duration
//

#ifndef POISONED_H
#define POISONED_H

#include "StatusEffect.h"

class Game;

class Poisoned : public StatusEffect{
    bool poisonApplied = false;
public:
    Poisoned(int potency, int duration, Entity* target)
        : StatusEffect(potency, duration, target) {}
    ~Poisoned() override;
    Type GetType() const override {return Type::Poisoned;}
    std::string GetTypeAsString() override {return "Poison";}
    void Tick(Game* game) override;
};



#endif //POISONED_H
