//
// Created by nova on 7/21/25.
//

#include "OnFire.h"
#include "../Entity/Entity.h"


OnFire::~OnFire() {
}

void OnFire::Tick(Game* game) {
    target->TakeDamage(potency, game);
    DecrementDuration();
}
