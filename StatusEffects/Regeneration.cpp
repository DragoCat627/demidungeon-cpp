//
// Created by nova on 7/30/25.
//

#include "Regeneration.h"
#include "../Entity/Entity.h"

Regeneration::~Regeneration() {
}

void Regeneration::Tick(Game* game) {
    target->Heal(potency);
    DecrementDuration();
}
