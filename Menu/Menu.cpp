//
// Created by nova on 7/7/25.
//

#include <chrono>
#include <iostream>
#include <thread>

#include "../Game/Game.h"
#include "../Dungeon/RoomNode.h"
#include "../Item/Item.h"
#include "../Menu/Menu.h"
#include "../Entity/Player.h"
#include "../Entity/Entity.h"
#include "../StatusEffects/OnFire.h"
#include "../StatusEffects/Poisoned.h"
#include "../StatusEffects/Regeneration.h"
#include "../StatusEffects/StatusEffect.h"
#include "../Item/Potion.h"

int Menu::gameSpeed = 3;
int Menu::clearScreen = true;
int validChoice = 0;

Menu::State Menu::Run(State currentState) {
    switch (currentState) {
        case State::Main:
            return HandleMainMenu();
        case State::Options:
            return HandleOptionsMenu();
        case State::GameSpeed:
            return HandleGameSpeedMenu();
        case State::ClearScreen:
            return HandleClearScreenMenu();
        case State::Difficulty:
            return HandleDifficultyMenu();
        case State::Game:
            return HandleGameMenu();
        case State::Move:
            return HandleMoveMenu();
        case State::Combat:
            return HandleCombatMenu();
        case State::Attack:
            return HandleAttackMenu();
        case State::UsePotion:
            return HandlePotionMenu();
        case State::Inventory:
            return HandleInventoryMenu();
        case State::Shop:
            return HandleShopMenu();
        case State::ShopBuy:
            return HandleShopBuyMenu();
        case State::ShopSell:
            return HandleShopSellMenu();
        case State::GameOver:
            return HandleGameOverMenu();
        case State::Stats:
            return HandleStatsMenu();
        default:
            return State::Exit;
    }
}

Menu::State Menu::HandleMainMenu() {
    Delay(2);
    ClearScreen();
    std::cout << "   DEMIDUNGEON" << std::endl
              << std::endl
              << "1) Start Game" << std::endl
              << "2) Options" << std::endl
              << "3) Exit" << std::endl;

    GetInput(3);
    switch (static_cast<MainChoice>(validChoice)) {
        case MainChoice::StartGame:
            currentGame = new Game();
            return State::Difficulty;
        case MainChoice::Options:
            return State::Options;
        case MainChoice::Exit:
            return State::Exit;
    }
    return State::Main;
}



Menu::State Menu::HandleOptionsMenu() {
    Delay(2);
    ClearScreen();
    ClearScreen();
    std::cout << "Select Option:" << std::endl
              << "1) Game Speed" << std::endl
              << "2) Screen Clearing" << std::endl
              << "3) Back" << std::endl;

    GetInput(3);
    switch (static_cast<OptionsChoice>(validChoice)) {
        case OptionsChoice::GameSpeed:
            return State::GameSpeed;
        case OptionsChoice::ScreenClearing:
            return State::ClearScreen;
        case OptionsChoice::Exit:
            return State::Main;
    }
    return State::Options;
}

Menu::State Menu::HandleGameSpeedMenu() {
    Delay(2);
    ClearScreen();
    std::cout << "Select Game Speed:" << std::endl
              << "1) Slow" << std::endl
              << "2) Medium" << std::endl
              << "3) Fast" << std::endl
              << "4) No Delay" << std::endl;

    GetInput(4);
    switch (static_cast<GameSpeedChoice>(validChoice)) {
        case GameSpeedChoice::Slow:
            SetGameSpeed(5);
        case GameSpeedChoice::Medium:
            SetGameSpeed(3);
        case GameSpeedChoice::Fast:
            SetGameSpeed(1);
        case GameSpeedChoice::NoDelay:
            SetGameSpeed(0);
    }
    return State::Options;
}

Menu::State Menu::HandleClearScreenMenu() {
    Delay(2);
    ClearScreen();
    std::cout << "Clear the screen occasionally?" << std::endl
              << "1) Yes" << std::endl
              << "2) No" << std::endl;

    GetInput(2);
    switch (static_cast<ClearScreenChoice>(validChoice)) {
        case ClearScreenChoice::Yes:
            clearScreen = true;
        case ClearScreenChoice::No:
            clearScreen = false;
    }
    return State::Options;
}

Menu::State Menu::HandleDifficultyMenu() {
    Delay(2);
    ClearScreen();
    std::cout << "Select Difficulty:" << std::endl
              << "1) Easy" << std::endl
              << "2) Normal" << std::endl
              << "3) Hard" << std::endl;

    GetInput(3);
    switch (static_cast<DifficultyChoice>(validChoice)) {
        case DifficultyChoice::Easy:
            currentGame->SetDifficulty(1);
            break;
        case DifficultyChoice::Normal:
            currentGame->SetDifficulty(2);
            break;
        case DifficultyChoice::Hard:
            currentGame->SetDifficulty(3);
            break;
    }
    currentGame->InitializeGame();
    currentPlayerInventory = currentGame->GetPlayer()->GetInventory();
    return State::Game;
}

Menu::State Menu::HandleGameMenu() {
    Delay(2);
    ClearScreen();
    currentGame->GetDungeon()->PrintDungeonGrid();
    std::cout << "1) Move" << std::endl
              << "2) Inventory" << std::endl
              << "3) Exit" << std::endl;

    GetInput(3);
    switch (static_cast<GameChoice>(validChoice)) {
        case GameChoice::Move:
            return State::Move;
        case GameChoice::Inventory:
            return State::Inventory;
        case GameChoice::Exit:
            return State::Main;
    }
    return State::Game;
}

Menu::State Menu::HandleMoveMenu() {
    ClearScreen();
    currentGame->GetDungeon()->PrintDungeonGrid();
    std::cout << "1) North" << std::endl
              << "2) East" << std::endl
              << "3) South" << std::endl
              << "4) West" << std::endl
              << "5) Exit" << std::endl;

    GetInput(5);
    switch (static_cast<MoveChoice>(validChoice)) {
        case MoveChoice::North:
            return HandleEncounter(currentGame->GetCurrentRoom()->GetNorth(), currentGame);
        case MoveChoice::East:
            return HandleEncounter(currentGame->GetCurrentRoom()->GetEast(), currentGame);
        case MoveChoice::South:
            return HandleEncounter(currentGame->GetCurrentRoom()->GetSouth(), currentGame);
        case MoveChoice::West:
            return HandleEncounter(currentGame->GetCurrentRoom()->GetWest(), currentGame);
        case MoveChoice::Exit:
            return State::Game;
    }
    return State::Move;
}


Menu::State Menu::HandleShopMenu() {
    Delay(2);
    ClearScreen();

    currentShopInventory = currentGame->GetCurrentRoom()->GetShopInventory();

    std::cout << "Shopkeeper's Stock:" << std::endl;
    currentShopInventory->PrintInventory();
    std::cout << "Your Gold: " << currentGame->GetPlayer()->GetGold() << std::endl;
    std::cout << "1) Buy Items" << std::endl
              << "2) Sell Items" << std::endl
              << "3) Sort Items" << std::endl
              << "4) Leave Shop"  << std::endl;

    GetInput(4);
    switch (static_cast<ShopChoice>(validChoice)) {
        case ShopChoice::Buy:
            return State::ShopBuy;
        case ShopChoice::Sell:
            return State::ShopSell;
        case ShopChoice::Sort:
            HandleSortParameterMenu(currentShopInventory);
            return State::Shop;
        case ShopChoice::Exit:
            return State::Exit;
    }
    return State::Shop;
}

Menu::State Menu::HandleShopBuyMenu() {
    Delay(2);
    ClearScreen();

    currentShopInventory = currentGame->GetCurrentRoom()->GetShopInventory();

    currentShopInventory->PrintInventory();
    std::cout << "Your Gold: " << currentGame->GetPlayer()->GetGold() << std::endl;
    std::cout << "Enter the ID of the item you would like to buy" << std::endl;

    if (ValidItemIDInput(currentShopInventory, Item::Type::None)) {
        currentPlayerInventory->AddToFront(currentShopInventory->GetItemWithID(id));
        currentGame->GetPlayer()->RemoveGold(currentShopInventory->GetItemWithID(id)->GetValue());
        currentShopInventory->RemoveItemWithID(id);
        std::cout << "Transaction complete" << std::endl;
        currentGame->AddItemsFound(1);
        Delay(3);
    }
    return State::Shop;
}

Menu::State Menu::HandleShopSellMenu() {
    Delay(2);
    ClearScreen();

    currentShopInventory = currentGame->GetCurrentRoom()->GetShopInventory();

    currentPlayerInventory->PrintInventory();
    std::cout << "Your Gold: " << currentGame->GetPlayer()->GetGold() << std::endl;
    std::cout << "Enter ID of item you would like to sell, or EXIT to exit:" << std::endl;

    if (ValidItemIDInput(currentPlayerInventory, Item::Type::None)) {
        currentShopInventory->AddToFront(currentPlayerInventory->RemoveItemWithID(id));
        currentGame->GetPlayer()->AddGold(currentPlayerInventory->GetItemWithID(id)->GetValue(), currentGame);
        std::cout << "Transaction complete" << std::endl;
    }
    return State::Shop;
}

Menu::State Menu::HandleCombatMenu() {
    Delay(2);
    ClearScreen();

    currentCombatQueue = currentGame->GetCurrentRoom()->GetCombatQueue();
    currentCombatQueue->Print(currentGame->GetPlayer());
    std::cout << "1) Attack" << std::endl
              << "2) Use Potion" << std::endl
              << "3) Flee" << std::endl;

    GetInput(3);
    switch (static_cast<CombatChoice>(validChoice)) {
        case CombatChoice::Attack:
            return State::Attack;
        case CombatChoice::UsePotion:
            return State::UsePotion;
        case CombatChoice::Flee:
            playerFled = true;
            return State::Exit;
    }
    return State::Combat;
}

Menu::State Menu::HandleAttackMenu() {
    Delay(2);
    ClearScreen();

    currentCombatQueue = currentGame->GetCurrentRoom()->GetCombatQueue();

    currentCombatQueue->Print(currentGame->GetPlayer());

    std::cout << "Enter ID of the enemy you would like to attack, or EXIT to exit:" << std::endl;
    if (!ValidEntityIDInput(currentCombatQueue)) {
        return State::Exit;
    }
    Entity* target = currentCombatQueue->GetEntityWithID(id);
    Weapon* currentWeapon = currentGame->GetPlayer()->GetCurrentWeapon();

    target->TakeDamage(std::stoi(currentWeapon->GetDamage()), currentGame);
    std::cout << target->GetEntityName() << " has taken " << std::max(std::stoi(currentWeapon->GetDamage()) - target->GetDefense(), 1) << " damage" << std::endl;

    if (currentWeapon->GetEffect() != Item::Effect::None) {
        if (currentWeapon->GetEffect() == Item::Effect::Fire) {
            auto* fire = new OnFire(currentWeapon->GetDamage(Inventory::SortOrder::Ascending) / 4, currentWeapon->GetDamage(Inventory::SortOrder::Ascending) / 8, target);
            target->ApplyStatusEffect(fire);
            std::cout << target->GetEntityName() << " has been set on fire" << std::endl;
            Delay(2);
        }
        else if (currentWeapon->GetEffect() == Item::Effect::Poison) {
            auto* poison = new Poisoned(currentWeapon->GetDamage(Inventory::SortOrder::Ascending) / 4, currentWeapon->GetDamage(Inventory::SortOrder::Ascending) / 8, target);
            target->ApplyStatusEffect(poison);
            std::cout << target->GetEntityName() << " has been poisoned" << std::endl;
            Delay(2);
        }
    }
    return State::Exit;
}


Menu::State Menu::HandlePotionMenu() {
    Delay(2);
    ClearScreen();

    currentCombatQueue = currentGame->GetCurrentRoom()->GetCombatQueue();

    currentPlayerInventory->SortInventory(Inventory::SortParameter::Potency, Inventory::SortOrder::Ascending);
    currentPlayerInventory->PrintInventory();

    std::cout << "Enter ID of potion you would like to use, or EXIT to exit:" << std::endl;
    if (ValidItemIDInput(currentPlayerInventory, Item::Type::Potion)) {
        auto* currentPotion = dynamic_cast<Potion*>(currentGame->GetPlayer()->GetInventory()->GetItemWithID(id));

        std::cout << "Enter the ID of the entity you would like to target with this potion, or EXIT to exit:" << std::endl;
        if (ValidEntityIDInput(currentCombatQueue)) {
            Entity* target = currentCombatQueue->GetEntityWithID(id);

            if (currentPotion->GetEffect() == Item::Effect::Fire) {
                auto* fire = new OnFire(currentPotion->GetPotency(Inventory::SortOrder::Ascending), currentPotion->GetPotency(Inventory::SortOrder::Ascending), target);
                target->ApplyStatusEffect(fire);
                std::cout << target->GetEntityName() << " has been set on fire" << std::endl;
                Delay(2);
            }
            else if (currentPotion->GetEffect() == Item::Effect::Poison) {
                auto* poison = new Poisoned(currentPotion->GetPotency(Inventory::SortOrder::Ascending), currentPotion->GetPotency(Inventory::SortOrder::Ascending), target);
                target->ApplyStatusEffect(poison);
                std::cout << target->GetEntityName() << " has been set poisoned" << std::endl;
                Delay(2);
            }
            else if (currentPotion->GetEffect() == Item::Effect::Regeneration) {
                auto* regeneration = new Regeneration(currentPotion->GetPotency(Inventory::SortOrder::Ascending), currentPotion->GetPotency(Inventory::SortOrder::Ascending), target);
                target->ApplyStatusEffect(regeneration);
                std::cout << target->GetEntityName() << " is now regenerating health" << std::endl;
                Delay(2);
            }
        }
    }
    return State::Combat;
}

Menu::State Menu::HandleInventoryMenu() {
    Delay(2);
    ClearScreen();
    currentGame->GetPlayer()->GetInventory()->PrintInventory();

    std::cout << "1) Sort" << std::endl
              << "2) Equip Weapon" << std::endl
              << "3) Equip Armor" << std::endl
              << "4) Exit" << std::endl;

    GetInput(4);
    switch (static_cast<InventoryChoice>(validChoice)) {
        case InventoryChoice::Sort:
            return HandleSortParameterMenu(currentPlayerInventory);
        case InventoryChoice::EquipWeapon: {
            std::cout << "Enter ID of Weapon you would like to equip, or EXIT to exit:" << std::endl;
            if (ValidItemIDInput(currentPlayerInventory, Item::Type::Weapon)) {
                currentGame->GetPlayer()->SetCurrentWeapon(dynamic_cast<Weapon*>(currentPlayerInventory->GetItemWithID(id)));
                currentGame->GetPlayer()->GetInventory()->RemoveItemWithID(id);
                std::cout << "Weapon equipped." << std::endl;
                Delay(2);
            }
            return State::Inventory;
        }
        case InventoryChoice::EquipArmor: {
            std::cout << "Enter ID of Armor you would like to equip, or EXIT to exit:" << std::endl;
            if (ValidItemIDInput(currentPlayerInventory, Item::Type::Armor)) {
                currentGame->GetPlayer()->SetCurrentArmor(dynamic_cast<Armor*>(currentPlayerInventory->GetItemWithID(id)));
                currentGame->GetPlayer()->GetInventory()->RemoveItemWithID(id);
                std::cout << "Armor equipped" << std::endl;
                Delay(2);
                return State::Inventory;
            }
        }
        case InventoryChoice::Exit:
            return State::Game;

        default:
            return State::Inventory;
    }
}

Menu::State Menu::HandleSortParameterMenu(Inventory* inventoryToSort) {
    Delay(2);
    ClearScreen();
    std::cout << "Choose a metric to sort by:" << std::endl
              << "1) ID" << std::endl
              << "2) Value" << std::endl
              << "3) Type" << std::endl
              << "4) Effect" << std::endl
              << "5) Damage" << std::endl
              << "6) Defense" << std::endl
              << "7) Potency" << std::endl
              << "8) Duration" << std::endl
              << "9) Exit" << std::endl;

    GetInput(9);
    if (validChoice == 9) {
        return State::Inventory;
    }
    switch (static_cast<Inventory::SortParameter>(validChoice)) {
        case Inventory::SortParameter::ID:
            return HandleSortOrderMenu(inventoryToSort, Inventory::SortParameter::ID);
        case Inventory::SortParameter::Value:
            return HandleSortOrderMenu(inventoryToSort, Inventory::SortParameter::Value);
        case Inventory::SortParameter::Type:
            return HandleSortOrderMenu(inventoryToSort, Inventory::SortParameter::Type);
        case Inventory::SortParameter::Effect:
            return HandleSortOrderMenu(inventoryToSort, Inventory::SortParameter::Effect);
        case Inventory::SortParameter::Damage:
            return HandleSortOrderMenu(inventoryToSort, Inventory::SortParameter::Damage);
        case Inventory::SortParameter::Defense:
            return HandleSortOrderMenu(inventoryToSort, Inventory::SortParameter::Defense);
        case Inventory::SortParameter::Potency:
            return HandleSortOrderMenu(inventoryToSort, Inventory::SortParameter::Potency);
        case Inventory::SortParameter::Duration:
            return HandleSortOrderMenu(inventoryToSort, Inventory::SortParameter::Duration);
    }
    return State::SortParameter;
}

Menu::State Menu::HandleSortOrderMenu(Inventory* inventoryToSort, Inventory::SortParameter sortParameter) {
    Delay(2);
    ClearScreen();
    std::cout << "1) Ascending" << std::endl
              << "2) Descending" << std::endl;

    GetInput(2);
    switch (static_cast<Inventory::SortOrder>(validChoice)) {
        case Inventory::SortOrder::Ascending:
            inventoryToSort->SortInventory(sortParameter, Inventory::SortOrder::Ascending);
            std::cout << "Inventory sorted" << std::endl;
            return State::Inventory;
        case Inventory::SortOrder::Descending:
            inventoryToSort->SortInventory(sortParameter, Inventory::SortOrder::Descending);
            std::cout << "Inventory sorted" << std::endl;
            return State::Inventory;
    }
    return State::SortOrder;
}

Menu::State Menu::HandleGameWinMenu() {
    Delay(2);
    ClearScreen();
    std::cout << "YOU WON" << std::endl
              << "1) Stats" << std::endl
              << "2) Main Menu" << std::endl
              << "3) Exit Game" << std::endl;

    GetInput(3);
    switch (static_cast<GameWinChoice>(validChoice)) {
        case GameWinChoice::Stats:
            return State::Stats;
        case GameWinChoice::MainMenu:
            return State::Main;
        case GameWinChoice::Exit:
            return State::Exit;
    }
    return State::GameWin;
}

Menu::State Menu::HandleGameOverMenu() {
    Delay(2);
    ClearScreen();
    std::cout << "GAME OVER" << std::endl
              << "1) Stats" << std::endl
              << "2) Main Menu" << std::endl
              << "3) Exit Game" << std::endl;

    GetInput(3);
    switch (static_cast<GameOverChoice>(validChoice)) {
        case GameOverChoice::Stats:
            return State::Stats;
        case GameOverChoice::MainMenu:
            return State::Main;
        case GameOverChoice::Exit:
            return State::Exit;
    }
    return State::GameOver;
}

Menu::State Menu::HandleStatsMenu() {
    Delay(2);
    ClearScreen();
    currentGame->PrintStats();
    std::cout << "1) Exit" << std::endl;

    GetInput(1);
    return State::Exit;
}

Player* Menu::GetCurrentPlayer() const {
    return currentGame->GetPlayer();
}

RoomNode* Menu::GetCurrentRoom() const {
    return currentGame->GetCurrentRoom();
}

void Menu::GetInput(int numOptions) {
    std::cin >> userChoice;
    while (!ValidInputChoice(userChoice, numOptions)) {
        Delay(2);
        std::cout << "Invalid input. Please enter a number between 1 and " << numOptions << ": ";
        std::cin.clear();
        std::cin >> userChoice;
    }
}

void Menu::GetInput(int numOptions, const std::string extraOption) {
    std::cin >> userChoice;
    if (userChoice == extraOption) {
        return;
    }
    while (!ValidInputChoice(userChoice, numOptions)) {
        Delay(2);
        std::cout << "Invalid input. Please enter a number between 1 and " << numOptions << ": ";
        std::cin.clear();
        std::cin >> userChoice;
    }
}

bool Menu::ValidInputChoice(const std::string userChoice, int numOptions) {
    try {
        int temp = std::stoi(userChoice);
        if (temp > 0 && temp <= numOptions) {
            validChoice = temp;
            return true;
        }
    }
    catch (...) {
        return false;
    }
    return false;
}

bool Menu::ValidItemIDInput(Inventory* itemLocation, Item::Type itemType) {
    while (true) {
        std::cin >> userChoice;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input." << std::endl;
            continue;
        }

        if (userChoice == "EXIT") {
            return false;
        }

        try {
            id = std::stoi(userChoice);
        }
        catch (...) {
            std::cout << "Invalid input." << std::endl;
            continue;
        }

        if (!itemLocation->HasItemWithID(id)) {
            std::cout << "No item exists with ID: " << id << std::endl;
            continue;
        }

        if (itemType == Item::Type::Weapon) {
            auto* weapon = dynamic_cast<Weapon*>(itemLocation->GetItemWithID(id));
            if (!weapon) {
                std::cout << "Item with ID: " << id << " is not a Weapon" << std::endl;
                continue;
            }
        }
        else if (itemType == Item::Type::Armor) {
            auto* armor = dynamic_cast<Armor*>(itemLocation->GetItemWithID(id));
            if (!armor) {
                std::cout << "Item with ID: " << id << " is not Armor" << std::endl;
                continue;
            }
        }
        else if (itemType == Item::Type::Potion) {
            auto* potion = dynamic_cast<Potion*>(itemLocation->GetItemWithID(id));
            if (!potion) {
                std::cout << "Item with ID: " << id << " is not a Potion" << std::endl;
                continue;
            }
        }

        return true;
    }
}

bool Menu::ValidEntityIDInput(CombatQueue* entityLocation) {
    while (true) {
        std::cin >> userChoice;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input." << std::endl;
            continue;
        }

        if (userChoice == "EXIT") {
            return false;
        }

        try {
            id = std::stoi(userChoice);
        }
        catch (...) {
            std::cout << "Invalid input." << std::endl;
            continue;
        }

        if (entityLocation->GetEntityWithID(id) != nullptr) {
            return true;
        }
    }
}

void Menu::Delay(int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds( 100 * delay * GetGameSpeed()));
}

void Menu::ClearScreen() {
    if (clearScreen) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
# endif
    }
}

void Menu::SetGameSpeed(int choice) {
    gameSpeed = choice;
}

int Menu::GetGameSpeed() {
    return gameSpeed;
}

Menu::State Menu::HandleEncounter(RoomNode* moveAttempt, Game* game) {
    if (moveAttempt != nullptr) {
        currentGame->GetCurrentRoom()->SetPlayerLocationStatus(false);
        currentGame->SetCurrentRoom(moveAttempt);
        currentGame->GetCurrentRoom()->SetPlayerLocationStatus(true);
        switch (currentGame->GetCurrentRoom()->RunRoom(this, currentGame->GetPlayer(), game)) {
            case RoomNode::clearType::BossWin:
                return State::GameWin;
            case RoomNode::clearType::Clear:
                return State::Game;
            case RoomNode::clearType::Loss:
                return State::GameOver;
            default:
                return State::Game;
        }
    }
    Delay(2);
    std::cout << "Invalid move. Please try again." << std::endl;
    return State::Move;
}
