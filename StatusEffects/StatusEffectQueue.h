//
// Created by nova on 7/22/25.
// Queue ADT implementation for holding the status effects on an entity
//

#ifndef STATUSEFFECTQUEUE_H
#define STATUSEFFECTQUEUE_H

#include "StatusEffect.h"
#include "../ADTBaseClasses/Queue.h"

class StatusEffectQueue : public Queue<StatusEffect> {
    bool ContainsEffect(StatusEffect* effect) const;
public:
    void Enqueue(StatusEffect* effect) override;
};



#endif //STATUSEFFECTQUEUE_H
