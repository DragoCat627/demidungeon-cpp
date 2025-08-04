cmake_minimum_required(VERSION 3.28.3)
project(CSC_1061_Capstone)

set(CMAKE_CXX_STANDARD 20)

add_executable(CSC_1061_Capstone main.cpp
        Menu/Menu.cpp
        Menu/Menu.h
        Entity/Entity.cpp
        Entity/Entity.h
        StatusEffects/StatusEffect.cpp
        StatusEffects/StatusEffect.h
        Item/Item.cpp
        Item/Item.h
        Combat/CombatQueue.cpp
        Combat/CombatQueue.h
        Game/Game.cpp
        Game/Game.h
        Item/Weapon.cpp
        Item/Weapon.h
        Item/Armor.cpp
        Item/Armor.h
        Item/Potion.cpp
        Item/Potion.h
        Entity/Enemy.cpp
        Entity/Enemy.h
        Entity/Player.cpp
        Entity/Player.h
        StatusEffects/OnFire.cpp
        StatusEffects/OnFire.h
        ADTBaseClasses/List.h
        ADTBaseClasses/DoublyLinkedNode.h
        ADTBaseClasses/Queue.h
        ADTBaseClasses/SinglyLinkedNode.h
        StatusEffects/StatusEffectQueue.cpp
        StatusEffects/StatusEffectQueue.h
        StatusEffects/Poisoned.cpp
        StatusEffects/Poisoned.h
        Dungeon/RoomNode.cpp
        Dungeon/RoomNode.h
        Dungeon/DungeonGrid.cpp
        Dungeon/DungeonGrid.h
        Combat/Combat.cpp
        Combat/Combat.h
        Item/Inventory.cpp
        Item/Inventory.h
        ADTBaseClasses/Stack.h
        StatusEffects/Regeneration.cpp
        StatusEffects/Regeneration.h
)
