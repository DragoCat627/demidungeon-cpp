//
// Created by nova on 7/25/25.
// Grid ADT for the map of the Dungeon
// Implemented using a quadruply-linked list
//

#ifndef DUNGEONGRID_H
#define DUNGEONGRID_H

#include "DungeonGrid.h"

class RoomNode;
class Game;

class DungeonGrid {
    int height;
    int width;

    RoomNode* bossRoom;
    RoomNode* startRoom;
public:
    DungeonGrid(int height, int width, const Game* game);
    ~DungeonGrid() {}

    RoomNode* GetBossRoom() const {return bossRoom;}
    RoomNode* GetStartRoom() const {return startRoom;}

    void SetBossRoom(RoomNode* bossRoom) {this->bossRoom = bossRoom;}
    void SetStartRoom(RoomNode* startRoom) {this->startRoom = startRoom;}

    void PrintDungeonGrid() const;
};



#endif //DUNGEONGRID_H
