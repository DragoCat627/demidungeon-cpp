//
// Created by nova on 7/8/25.
//

#include "Entity.h"

#include <iomanip>
#include <iostream>
#include <bits/ostream.tcc>

#include "../StatusEffects/StatusEffect.h"
#include "../Game/Game.h"

int Entity::nextID = 1;

void Entity::TickStatusEffects(Game* game) {
    StatusEffect* currentEffect;
    // Iterate through every status effect in the queue
    for (int i = 0; i < statusEffects->GetSize(); i++) {
        currentEffect = statusEffects->Dequeue();
        currentEffect->Tick(game);
        // If the effect still has duration, add it to the back of the queue
        if (currentEffect->GetDuration() > 0) {
            statusEffects->Enqueue(currentEffect);
            continue;
        }
        // Otherwise the effect will be deleted
        std::cout << "Effect has worn off" << std::endl;
        delete currentEffect;
        Menu::Delay(2);
    }
}

void Entity::TakeDamage(int amount, Game* game, bool ignoreDefense) {
    int totalDamage;
    // Damages the entity adjusting for their defense
    // Negative damage doesn't make sense so the max function is used
    if (!ignoreDefense) {
        totalDamage = std::max(amount - defense, 1);
    }
    else {
        totalDamage = amount;
    }
    health -= totalDamage;

    // Update the game statistics
    if (IsPlayer()) {
        game->AddDamageTaken(totalDamage);
    }
    else {
        game->AddDamageDealt(totalDamage);
    }
}
