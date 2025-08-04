//
// Created by nova on 7/26/25.
// Class for handling the main combat loop
//

#ifndef COMBAT_H
#define COMBAT_H

#include "CombatQueue.h"
#include "../Entity/Enemy.h"


class Combat {
public:
    static bool RunCombat(CombatQueue* combatQueue, Player* player, Menu* menu, Game* game);
};



#endif //COMBAT_H
