//
// Created by nova on 7/21/25.
// Enemy object will be created upon the player entering a combat room.
// Upon creation, they will be added to the combat queue and combat will start.
// There will be a few different types of enemies.
// Each will have a chance to inflict a unique status effect on the player when attacking.
// The higher the local difficulty in the room and the higher the overall difficulty,
// the higher that chance is, and the higher their stats will be.
//

#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
    int baseDamage;
    int effectChance;
public:
    enum class EffectType {
        None = 0,
        Fire = 1,
        Poison = 2
    };

    EffectType effectType;

    Enemy(EffectType effectType, int baseDamage, int effectChance, int health, int defense, Type type = Type::Enemy)
        : effectType(effectType), baseDamage(baseDamage), effectChance(effectChance), Entity(health, defense, type){}
    ~Enemy() override = default;

    void TakeTurn(Menu* menu, Game* game) override;
    std::string GetEntityName() override;
    int GetBaseDamage() const {return baseDamage;}
    int GetEffectChance() const {return effectChance;}
    bool IsPlayer() const override {return false;}
};


#endif //ENEMY_H
