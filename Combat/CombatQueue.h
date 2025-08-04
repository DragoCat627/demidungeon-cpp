//
// Created by nova on 7/9/25.
// Queue ADT implementation for handling turn order during combat.
// Holds entity objects and has some combat related helper functions
//

#ifndef COMBATQUEUE_H
#define COMBATQUEUE_H

#include "../Entity/Entity.h"
#include "../ADTBaseClasses/Queue.h"
#include "../ADTBaseClasses/SinglyLinkedNode.h"


class Game;
class Player;

class CombatQueue : public Queue<Entity> {
public:
    CombatQueue() = default;

    void RemoveEntity(const Entity* entity);

    SinglyLinkedNode<Entity>* GetCombatFront() const {return front;}
    Entity* GetEntityWithID(int id) const;

    void CleanUpDead(Game* game);
    int EnemiesRemaining();

    void Print(Player* player) const;
};





#endif //COMBATQUEUE_H
