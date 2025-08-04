//
// Created by nova on 7/9/25.
//

#include <iomanip>
#include <iostream>

#include "CombatQueue.h"
#include "../Entity/Player.h"
#include "../Game/Game.h"

// Finds and removes a specific entity
void CombatQueue::RemoveEntity(const Entity* entity) {
    if (IsEmpty()) {
        return;
    }

    if (front->GetObject() == entity) {
        Dequeue();
        return;
    }

    SinglyLinkedNode<Entity>* previous = front;
    SinglyLinkedNode<Entity>* current = front->GetNext();

    for (int i = 0; i < size; i++) {
        if (current->GetObject() == entity) {
            previous->SetNext(current->GetNext());
            delete current;
            return;
        }
        previous = current;
        current = current->GetNext();
    }
}

Entity* CombatQueue::GetEntityWithID(int id) const {
    SinglyLinkedNode<Entity>* currentNode = GetCombatFront();
    while (currentNode) {
        if (currentNode->GetObject()->GetID() == id) {
            return currentNode->GetObject();
        }
        currentNode = currentNode->GetNext();
    }
    return nullptr;
}

// Removes all entities from the status effect queue that have <= 0 health
void CombatQueue::CleanUpDead(Game* game) {
    SinglyLinkedNode<Entity>* currentNode = GetCombatFront();
    if (currentNode == nullptr) {
        return;
    }
    SinglyLinkedNode<Entity>* nextNode = currentNode->GetNext();
    while (nextNode) {
        if (currentNode->GetObject()->GetHealth() <= 0) {
            std::cout << currentNode->GetObject()->GetEntityName() << " is dead, removing them from combat" << std::endl;
            game->AddEnemiesKilled(1);
            RemoveEntity(currentNode->GetObject());
        }
        currentNode = nextNode;
        nextNode = nextNode->GetNext();
    }
}

// Returns the number of entities currently in the queue
int CombatQueue::EnemiesRemaining() {
    int count = 0;
    SinglyLinkedNode<Entity>* current = GetCombatFront();
    while (current != nullptr) {
        Entity* entity = current->GetObject();
        if (!entity->IsPlayer() && entity->IsAlive()) {
            count++;
        }
        current = current->GetNext();
    }
    return count;
}

// Prints every enemy in the queue along with their ID, Health, Defense, and any Status Effects and their duration and potency
void CombatQueue::Print(Player* player) const {
    SinglyLinkedNode<Entity>* currentCombatNode = GetCombatFront();
    const int width = 20;

    // Prints the header row
    std::cout << std::left
              << std::setw(width) << "Name"
              << std::setw(width / 2) << "ID"
              << std::setw(width / 2) << "Health"
              << std::setw(width / 2) << "Defense"
              << std::setw(width / 2) << "Status Effects [type/potency/duration]"
              << std::endl;

    std::cout << std::string(width * 5, '-') << std::endl;

    // Because the print is called on the player's turn, they are not in the combat queue and need to be handled separately

    // Prints the player information
    std::cout << std::left
              << std::setw(width) << player->GetEntityName()
              << std::setw(width / 2) << player->GetID()
              << std::setw(width / 2) << player->GetHealth()
              << std::setw(width / 2) << player->GetDefense();

    // Prints the player's status effects if they have any
    SinglyLinkedNode<StatusEffect>* currentEffectNode;
    if (!player->GetStatusEffectQueue()->IsEmpty()) {
        currentEffectNode = player->GetStatusEffectQueue()->GetFront();
        while (currentEffectNode) {
            std::cout << std::left
                      << std::setw(width / 2) << currentEffectNode->GetObject()->GetTypeAsString()
                      << std::setw(width / 2) << currentEffectNode->GetObject()->GetPotency()
                      << std::setw(width / 2) << currentEffectNode->GetObject()->GetDuration();
            currentEffectNode = currentEffectNode->GetNext();
        }
    }
    else {
        std::cout << std::left
                  << std::setw(width) << "None";
    }
    std::cout << std::endl
              << std::string(width * 5, '-') << std::endl;

    // Iterates through the queue and does the same for every enemy
    while (currentCombatNode != nullptr) {
        Entity* entity = currentCombatNode->GetObject();
        std::cout << std::left
                  << std::setw(width) << entity->GetEntityName()
                  << std::setw(width / 2) << entity->GetID()
                  << std::setw(width / 2) << entity->GetHealth()
                  << std::setw(width / 2) << entity->GetDefense();

        if (!entity->GetStatusEffectQueue()->IsEmpty()) {
            currentEffectNode = entity->GetStatusEffectQueue()->GetFront();
            while (currentEffectNode) {
                std::cout << std::left
                          << std::setw(width / 2) << currentEffectNode->GetObject()->GetTypeAsString()
                          << std::setw(width / 2) << currentEffectNode->GetObject()->GetPotency()
                          << std::setw(width / 2) << currentEffectNode->GetObject()->GetDuration();
                currentEffectNode = currentEffectNode->GetNext();
            }
        }
        else {
            std::cout << std::left
                      << std::setw(width) << "None";
        }

        std::cout << std::endl;
        currentCombatNode = currentCombatNode->GetNext();
    }
}

