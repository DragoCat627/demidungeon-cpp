//
// Created by nova on 7/22/25.
//

#include "StatusEffectQueue.h"
#include "../ADTBaseClasses/SinglyLinkedNode.h"

bool StatusEffectQueue::ContainsEffect(StatusEffect* effect) const {
    SinglyLinkedNode<StatusEffect>* currentNode = front;
    while (currentNode) {
        if (currentNode->GetObject() == effect) {
            return true;
        }
        currentNode = currentNode->GetNext();
    }
    return false;
}

void StatusEffectQueue::Enqueue(StatusEffect *effect) {
    if (!ContainsEffect(effect)) {
        Queue<StatusEffect>::Enqueue(effect);
    }
}

