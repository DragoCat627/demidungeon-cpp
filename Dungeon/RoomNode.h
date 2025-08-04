//
// Created by nova on 7/25/25.
// Nodes for the Grid ADT
//

#ifndef ROOM_H
#define ROOM_H

#include "DungeonGrid.h"
#include "../Combat/CombatQueue.h"
#include "../Item/Inventory.h"

class Player;
class Menu;

class RoomNode {
    RoomNode* north = nullptr;
    RoomNode* south = nullptr;
    RoomNode* east = nullptr;
    RoomNode* west = nullptr;

    int localDifficulty;

    bool isCleared = false;
    bool playerInRoom = false;

    Inventory* shopInventory;
    CombatQueue* combatQueue;
public:
    enum class Type {
        Start,
        Normal,
        Shop,
        Boss
    };

    Type roomType;

    enum class clearType {
        Clear = 1,
        Loss = 2,
        BossWin = 3,
    };

    RoomNode(int x, int y, int maxX, int maxY, const Game* game);
    ~RoomNode() = default;

    clearType RunRoom(Menu* menu, Player* player, Game* game);

    void PopulateEnemies(CombatQueue* combatQueue, Player* player) const;
    void PopulateShopInventory(Inventory* shopInventory) const;
    void PopulateBoss(CombatQueue* combatQueue, Player* player, int difficulty) const;

    Type GetType() const {return roomType;}

    RoomNode* GetNorth() const {return north;}
    RoomNode* GetSouth() const {return south;}
    RoomNode* GetEast() const {return east;}
    RoomNode* GetWest() const {return west;}

    int GetRoomDifficulty() const {return localDifficulty;}

    bool IsCleared() const {return isCleared;}
    bool IsPlayerIn() const {return playerInRoom;}

    int GetLocalDifficulty() const {return localDifficulty;}

    Inventory* GetShopInventory() const {return shopInventory;}
    CombatQueue* GetCombatQueue() const {return combatQueue;}

    void SetType(Type type) {this->roomType = type;}

    void SetNorth(RoomNode* north) {this->north = north;}
    void SetSouth(RoomNode* south) {this->south = south;}
    void SetEast(RoomNode* east) {this->east = east;}
    void SetWest(RoomNode* west) {this->west = west;}

    void SetRoomDifficulty(int difficulty) {localDifficulty = difficulty;}

    void SetPlayerLocationStatus(bool status) {playerInRoom = status;}
};



#endif //ROOM_H
