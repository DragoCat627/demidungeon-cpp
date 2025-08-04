//
// Created by nova on 7/7/25.
// Class for handling the many different menus in the game
//

#ifndef MENU_H
#define MENU_H
#include <string>

#include "../Item/Inventory.h"
#include "../Item/Item.h"

class Game;
class Player;
class Entity;
class CombatQueue;
class Inventory;
class RoomNode;

class Menu {
public:
    enum class State {
        Main,
        Options,
        GameSpeed,
        ClearScreen,
        Difficulty,
        Game,
        Move,
        Inventory,
        Sort,
        SortParameter,
        SortOrder,
        Combat,
        Attack,
        UsePotion,
        Shop,
        ShopBuy,
        ShopSell,
        GameOver,
        GameWin,
        Stats,
        Exit
    };

    enum class MainChoice {
        StartGame = 1,
        Options = 2,
        Exit = 3
    };

    enum class OptionsChoice {
        GameSpeed = 1,
        ScreenClearing = 2,
        Exit = 3
    };

    enum class GameSpeedChoice {
        Slow = 1,
        Medium = 2,
        Fast = 3,
        NoDelay = 4
    };

    enum class ClearScreenChoice {
        Yes = 1,
        No = 2
    };

    enum class DifficultyChoice {
        Easy = 1,
        Normal = 2,
        Hard = 3,
    };

    enum class GameChoice {
        Move = 1,
        Inventory = 2,
        Exit = 3
    };

    enum class MoveChoice {
        North = 1,
        East = 2,
        South = 3,
        West = 4,
        Exit = 5
    };

    enum class InventoryChoice {
        Sort = 1,
        EquipWeapon = 2,
        EquipArmor = 3,
        Exit = 4
    };

    enum class CombatChoice {
        Attack = 1,
        UsePotion = 2,
        Flee = 3
    };

    enum class EnemyChoice {
        Exit = 1,
    };

    enum class ShopChoice {
        Buy = 1,
        Sell = 2,
        Sort = 3,
        Exit = 4
    };

    enum class StatsChoice {
        Exit = 1
    };

    enum class GameOverChoice {
        Stats = 1,
        MainMenu = 2,
        Exit = 3
    };

    enum class GameWinChoice {
        Stats = 1,
        MainMenu = 2,
        Exit = 3
    };

    State Run(State currentState);

    void SetCurrentPlayerInventory(Inventory* inventory) {currentPlayerInventory = inventory;}
    Player* GetCurrentPlayer() const;
    RoomNode* GetCurrentRoom() const;
    bool IfPlayerFled() const {return playerFled;}
    void SetPlayerFled(bool fled) {playerFled = fled;}

    static void Delay(int delay);
    static void ClearScreen();
private:
    Game* currentGame = nullptr;
    Inventory* currentPlayerInventory = nullptr;
    Inventory*  currentShopInventory = nullptr;
    CombatQueue* currentCombatQueue = nullptr;
    bool playerFled = false;

    std::string userChoice;
    std::string temp;
    int id = 0;

    static int gameSpeed;
    static int clearScreen;

    void GetInput(int numOptions);
    void GetInput(int numOptions, std::string extraChoice);
    static bool ValidInputChoice(std::string userChoice, int numOptions);
    bool ValidItemIDInput(Inventory* itemLocation, Item::Type itemType);
    bool ValidEntityIDInput(CombatQueue* entityLocation);

    static void SetGameSpeed(int choice);
    static int GetGameSpeed();

    State HandleMainMenu();
    State HandleOptionsMenu();
    State HandleGameSpeedMenu();
    State HandleClearScreenMenu();
    State HandleDifficultyMenu();
    State HandleGameMenu();
    State HandleMoveMenu();
    State HandleInventoryMenu();
    State HandleEncounter(RoomNode* moveAttempt, Game* game);
    State HandleShopMenu();
    State HandleShopBuyMenu();
    State HandleShopSellMenu();
    State HandleCombatMenu();
    State HandleAttackMenu();
    State HandlePotionMenu();
    State HandleSortParameterMenu(Inventory* inventoryToSort);
    State HandleSortOrderMenu(Inventory* inventoryToSort, Inventory::SortParameter);
    State HandleGameWinMenu();
    State HandleGameOverMenu();
    State HandleStatsMenu();

};

#endif //MENU_H

