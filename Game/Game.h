//
// Created by nova on 7/10/25.
// Class for handling the current game and the player's statistics
//

#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>

#include "../Menu/Menu.h"
#include "../Game/Game.h"
#include "../Dungeon/RoomNode.h"

class InventoryList;
class Player;
class DungeonGrid;
class Menu;

class Game {
    std::string playerName;
    int difficulty;

    int enemiesKilled = 0;
    int itemsFound = 0;
    int goldFound = 0;
    int goldSpent = 0;
    int damageTaken = 0;
    int damageDealt = 0;
    int roomsCleared = 0;
    int shopsVisited = 0;

    Player* player;
    DungeonGrid* dungeon;
    RoomNode* currentRoom;
public:
    explicit Game();
    ~Game() = default;

    void InitializeGame();

    void SetPlayerName(std::string name) {playerName = name;}
    std::string GetPlayerName() {return playerName;}

    Player* GetPlayer() const {return player;}
    DungeonGrid* GetDungeon() const {return dungeon;}

    RoomNode* GetCurrentRoom() const {return currentRoom;}
    void SetCurrentRoom(RoomNode* room) {currentRoom = room;}

    void SetDifficulty(int choice) {difficulty = choice;}
    int GetDifficulty() const {return difficulty;}

    void SetEnemiesKilled(int number) {enemiesKilled = number;}
    void SetItemsFound(int number) {itemsFound = number;}
    void SetGoldFound(int number) {goldFound = number;}
    void SetDamageTaken(int number) {damageTaken = number;}
    void SetDamageDealt(int number) {damageDealt = number;}
    void SetRoomsCleared(int number) {roomsCleared = number;}
    void SetShopsVisited(int number) {shopsVisited = number;}

    int GetEnemiesKilled() const {return enemiesKilled;}
    int GetItemsFound() const {return itemsFound;}
    int GetGoldFound() const {return goldFound;}
    int GetDamageTaken() const {return damageTaken;}
    int GetDamageDealt() const {return damageDealt;}
    int GetRoomsCleared() const {return roomsCleared;}
    int GetShopsVisited() const {return shopsVisited;}

    void AddEnemiesKilled(int number) {enemiesKilled += number;}
    void AddItemsFound(int number) {itemsFound += number;}
    void AddGoldFound(int number) {goldFound += number;}
    void AddDamageTaken(int number) {damageTaken += number;}
    void AddDamageDealt(int number) {damageDealt += number;}
    void AddRoomsCleared(int number) {roomsCleared += number;}
    void AddShopsVisited(int number) {shopsVisited += number;}

    void PrintStats();
};



#endif //GAME_H
