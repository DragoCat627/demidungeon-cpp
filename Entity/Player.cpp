//
// Created by nova on 7/21/25.
//

#include <iostream>

#include "../Game/Game.h"
#include "Player.h"
#include "../Menu/Menu.h"

Player::Player() {
    inventory = new Inventory();
    health = 100;
    maxHealth = 100;
    defense = 0;
    entityID = nextID++;
    currentWeapon = new Weapon(0, 8);
    currentArmor = new Armor(0, 0);
}

void Player::Heal(int amount) {
    health += amount;
    // Health cannot exceed the max
    if (health > maxHealth) {
        health = maxHealth;
        std::cout << "Healed to full" << std::endl;
        return;
    }
    std::cout << "Healed to: " << health << std::endl;
}

// Adds gold and updates the game statistics
void Player::AddGold(int value, Game* game) {
    gold += value;
    game->AddGoldFound(value);
}

std::string Player::GetEntityName() {
    return "Player, " + playerName;
}

// Runs through the combat menus, then ticks the players status effects
void Player::TakeTurn(Menu* menu, Game* game) {
    Menu::State currentState = Menu::State::Combat;
    while (Menu::State::Exit != currentState) {
        currentState = menu->Run(currentState);
    }
    TickStatusEffects(game);
}

void Player::SetCurrentWeapon(Weapon* weapon) {
    inventory->AddToFront(currentWeapon);
    currentWeapon = weapon;
}

void Player::SetCurrentArmor(Armor* armor) {
    inventory->AddToFront(currentArmor);
    currentArmor = armor;
    defense = stoi(currentArmor->GetDefense());
}
