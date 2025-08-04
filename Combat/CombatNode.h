//
// Created by nova on 7/21/25.
// Node objects for the combat queue.
//

#ifndef COMBATNODE_H
#define COMBATNODE_H

#include "../Entity/Entity.h"

class CombatNode {
    CombatNode* next;
    Entity* entity;
public:
    explicit CombatNode(Entity* ent, CombatNode* nex = nullptr)
        : entity(ent), next(nex) {}

    CombatNode* getNext() const {return next;}
    Entity* getEntity() const {return entity;}
    void setNext(CombatNode* next) {this->next = next;}
};



#endif //COMBATNODE_H
