//
// Created by nova on 7/10/25.
//

#include "Game.h"

#include "../Dungeon/DungeonGrid.h"
#include "../Entity/Player.h"
#include <iostream>

Game::Game() {
    Menu::Delay(2);
    std::cout << "Enter your name:";
    std::cin >> playerName;
}

void Game::InitializeGame() {
    dungeon = new DungeonGrid(3 + difficulty * 2, 3 + difficulty * 2, this);
    std::cout << "Dungeon initialized" << std::endl;
    Menu::Delay(1);
    currentRoom = dungeon->GetStartRoom();
    player = new Player();
    player->SetName(playerName);
    std::cout << "Player initialized" << std::endl;
    Menu::Delay(1);
    std::cout << "Game initialized" << std::endl;
    Menu::Delay(1);
}

void Game::PrintStats() {
    std::cout << "Name:            " << playerName << std::endl
              << "Difficulty:      " << difficulty << std::endl
              << "Enemies killed:  " << enemiesKilled << std::endl
              << "Items found:     " << itemsFound << std::endl
              << "Gold found:      " << goldFound << std::endl
              << "Gold spent:      " << goldSpent << std::endl
              << "Damage dealt:    " << damageDealt << std::endl
              << "Damage taken:    " << damageTaken << std::endl
              << "Rooms cleared:   " << roomsCleared << std::endl
              << "Shops visited:   " << shopsVisited << std::endl;
}
