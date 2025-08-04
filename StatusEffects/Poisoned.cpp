//
// Created by nova on 7/25/25.
//

#include "Poisoned.h"
#include "OnFire.h"
#include "../Entity/Entity.h"

bool poisonApplied = false;

Poisoned::~Poisoned() {
    target->IncreaseDefense(potency);
}

void Poisoned::Tick(Game* game) {
    if (!poisonApplied) {
        target->ReduceDefense(potency);
        poisonApplied = true;
    }
    DecrementDuration();
}