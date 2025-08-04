//
// Created by nova on 7/21/25.
//


#include <iostream>

#include "Enemy.h"
#include "../Menu/Menu.h"
#include "../Entity/Player.h"
#include "../StatusEffects/StatusEffect.h"
#include "../StatusEffects/OnFire.h"
#include "../StatusEffects/Poisoned.h"

// Enemy turn function called during combat
void Enemy::TakeTurn(Menu* menu, Game* game) {

    // Get and damage the player
    Player* player = menu->GetCurrentPlayer();
    player->TakeDamage(baseDamage, game);
    std::cout << GetEntityName() << " did " << std::max(baseDamage - player->GetDefense(), 1) << " damage to you" << std::endl;
    Menu::Delay(2);

    // If the enemy has a special type, then they have a chance to inflict some status effect upon the player
    if (effectType != EffectType::None && effectChance > rand() % 100) {
        if (effectType == EffectType::Fire) {
            player->ApplyStatusEffect(new OnFire(baseDamage / 4 + 1, baseDamage / 8 + 1, player));
            std::cout << GetEntityName() << " has set you on fire" << std::endl;
            Menu::Delay(2);
        }
        else if (effectType == EffectType::Poison) {
            player->ApplyStatusEffect(new Poisoned(baseDamage / 4, baseDamage / 8, player));
            std::cout << GetEntityName() << " has poisoned you" << std::endl;
            Menu::Delay(2);
        }
    }
    TickStatusEffects(game);
}

std::string Enemy::GetEntityName() {
    if (effectType == EffectType::None) {
        return "Enemy, Goblin";
    }
    if (effectType == EffectType::Fire) {
        return "Enemy, Mage";
    }
    if (effectType == EffectType::Poison) {
        return "Enemy, Slime";
    }
    return "Enemy, Null";
}
