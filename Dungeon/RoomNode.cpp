//
// Created by nova on 7/25/25.
//

#include <cstdlib>
#include <algorithm>

#include "RoomNode.h"
#include "../Menu/Menu.h"
#include "../Game/Game.h"
#include "../Combat/Combat.h"
#include "../Item/Inventory.h"
#include "../Entity/Player.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/Potion.h"

class Inventory;

RoomNode::RoomNode(int x, int y, int maxX, int maxY, const Game* game) {
    int shopChance = rand() % 6;
    int difficultyNoise = rand() % 3 - 2;

    if (x == 1 && y == 1) {
        roomType = Type::Start;
        isCleared = true;
        playerInRoom = true;
    }
    else if (x == maxX && y == maxY) {
        roomType = Type::Boss;
    }
    else if (shopChance == 1) {
        roomType = Type::Shop;
    }
    else {
        roomType = Type::Normal;
    }

    // Difficulty scales with the distance from the start, the overall game difficulty, and some random noise
    localDifficulty = (x + y) / 4 + game->GetDifficulty() * 2 + difficultyNoise;
}

RoomNode::clearType RoomNode::RunRoom(Menu* menu, Player* player, Game* game) {
    // If the room was already cleared, do nothing
    if (isCleared) {
        std::cout << "Room is empty" << std::endl;
        return clearType::Clear;
    }
    isCleared = true;
    game->AddRoomsCleared(1);

    // If the room type is normal, generate some enemies based on local difficulty and start combat
    if (roomType == Type::Normal) {
        std::cout << "Room has hostile entities, starting combat" << std::endl;
        Menu::Delay(4);
        combatQueue = new CombatQueue();
        PopulateEnemies(combatQueue, player);

        // RunCombat returns true if the player survived the combat
        if (Combat::RunCombat(combatQueue, player, menu, game)) {
            std::cout << "Room cleared" << std::endl;
            Menu::Delay(4);
            return clearType::Clear;
        }
        return clearType::Loss;
    }

    // If the room is a shop, generate some items and allow the player to purchase them or sell their own
    if (roomType == Type::Shop) {
        std::cout << "A trader welcomes you in and invites you to browse her wares" << std::endl;
        game->AddShopsVisited(1);
        Menu::Delay(4);

        shopInventory = new Inventory();
        PopulateShopInventory(shopInventory);

        Menu::State currentState = Menu::State::Shop;
        while (currentState != Menu::State::Exit) {
            currentState = menu->Run(currentState);
        }

        std::cout << "You leave the shop" << std::endl;
        Menu::Delay(2);
        return clearType::Clear;
    }
    if (roomType == Type::Boss) {
        combatQueue = new CombatQueue();
        PopulateBoss(combatQueue, player, game->GetDifficulty());
        if (Combat::RunCombat(combatQueue, player, menu, game)) {
            return clearType::BossWin;
        }
        return clearType::Loss;
    }
    return clearType::Clear;
}

// Populates the combat queue by adding the player and some randomly generated enemies
void RoomNode::PopulateEnemies(CombatQueue* combatQueue, Player* player) const {
    combatQueue->Enqueue(player);
    int enemyAmount = localDifficulty / 3 + 1;
    for (int i = 0; i < enemyAmount; ++i) {
        auto* newEnemy = new Enemy(static_cast<Enemy::EffectType>(rand() % 3),
            localDifficulty + rand() % 6 - 2,
            std::min((localDifficulty * 4 + rand() % 10), 100),
            localDifficulty + rand() % 5 + 3,
            std::max(localDifficulty / 2 - rand() % 5, 0));
        combatQueue->Enqueue(newEnemy);
    }
}

// Populates the shop inventory with some random items
void RoomNode::PopulateShopInventory(Inventory* shopInventory) const {
    Weapon* newWeapon;
    Armor* newArmor;
    Potion* newPotion;
    Potion* newPotion2;
    int rareWeaponChance;
    for (int i = 0; i < localDifficulty / 2; i++) {
        // Small chance to generate a weapon that applies a random status effect
        rareWeaponChance = rand() % 7;
        if (rareWeaponChance == 1) {
            newWeapon = new Weapon(rand() % 5 + localDifficulty, rand() % 10 + localDifficulty, static_cast<Item::Effect>(rand() % 2 + 1));
        }
        else {
            newWeapon = new Weapon(rand() % 5 + localDifficulty, rand() % 10 + localDifficulty, static_cast<Item::Effect>(0));
        }
        newArmor = new Armor(rand() % 5 + localDifficulty, rand() % 3 + localDifficulty, static_cast<Item::Effect>(rand() % 2 + 1));
        newPotion = new Potion(rand() % 5 + localDifficulty, rand() % 3 + localDifficulty, localDifficulty / 2, static_cast<Item::Effect>(rand() % 2 + 1));
        newPotion2 = new Potion(rand() % 5 + localDifficulty, rand() % 3 + localDifficulty, localDifficulty / 2, static_cast<Item::Effect>(rand() % 2 + 1));

        shopInventory->AddToFront(newWeapon);
        shopInventory->AddToFront(newArmor);
        shopInventory->AddToFront(newPotion);
        shopInventory->AddToFront(newPotion2);
    }
}

// Adds the player and a single powerful enemy to the combat queue
void RoomNode::PopulateBoss(CombatQueue* combatQueue, Player* player, int difficulty) const {
    combatQueue->Enqueue(player);
    auto* newEnemy = new Enemy(static_cast<Enemy::EffectType>(1),
        localDifficulty + 10,
        100,
        50 * difficulty,
        localDifficulty);
    combatQueue->Enqueue(newEnemy);
}
