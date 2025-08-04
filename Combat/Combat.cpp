//
// Created by nova on 7/26/25.
//

#include <iostream>
#include <ostream>

#include "Combat.h"
#include "../Dungeon/RoomNode.h"
#include "../Menu/Menu.h"
#include "../Game/Game.h"
#include "../Item/Potion.h"
#include "../Entity/Player.h"

// Main combat loop, returns true if the player survived/won, returns false if they died
bool Combat::RunCombat(CombatQueue* combatQueue, Player* player, Menu* menu, Game* game) {
    Entity* currentEntity;
    while (true) {
        // Get the next entity.
        currentEntity = combatQueue->Dequeue();
        std::cout << "Starting " << currentEntity->GetEntityName() << "'s turn" << std::endl;
        Menu::Delay(1);

        // Take the turn of the next entity.
        currentEntity->TakeTurn(menu, game);

        if (menu->IfPlayerFled()) {
            std::cout << "Fleeing" << std::endl;
            Menu::Delay(3);
            menu->SetPlayerFled(false);
            player->GetStatusEffectQueue()->Clear();
            return true;
        }

        // Add the next entity to the back of the queue.
        if (currentEntity->GetHealth() > 0) {
            std::cout << currentEntity->GetEntityName() << "'s turn is over" << std::endl;
            Menu::Delay(6);
            Menu::ClearScreen();
            combatQueue->Enqueue(currentEntity);
        }

        // Remove entities with 0 health.
        combatQueue->CleanUpDead(game);
        Menu::Delay(3);

        // Player is dead, so combat is over and the player loses
        if (player->GetHealth() <= 0) {
            std::cout << "You died" << std::endl;
            return false;
        }

        // All enemies have been defeated and only the player remains,
        // so combat is over and the player wins and gets some loot.
        if (combatQueue->EnemiesRemaining() == 0) {
            int localDifficulty = menu->GetCurrentRoom()->GetLocalDifficulty();
            int goldFound = localDifficulty + 2;
            std::cout << "You won, and found " << goldFound << " gold" << std::endl;
            player->AddGold(goldFound, game);
            if (rand() % 4 == 1) {
                auto* newPotion = new Potion(localDifficulty, localDifficulty / 4 + 1, localDifficulty / 8 + 1, Item::Effect::Regeneration);
                player->AddItem(newPotion);
                std::cout << "And a regeneration potion" << std::endl;
                game->AddItemsFound(1);
            }
            player->GetStatusEffectQueue()->Clear();
            return true;
        }
    }
}
