//
// Created by nova on 7/21/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../Item/Armor.h"
#include "../Item/Weapon.h"

class Menu;
class InventoryList;

class Player : public Entity {
    int gold = 0;
    int maxHealth = 100;

    Weapon* currentWeapon = nullptr;
    Armor* currentArmor = nullptr;
    Inventory* inventory = nullptr;
    std::string playerName;
public:
    Player();

    void TakeTurn(Menu* menu, Game* game) override;

    Weapon* GetCurrentWeapon() const {return currentWeapon;}
    Armor* GetCurrentArmor() const  {return currentArmor;}

    Inventory* GetInventory() const {return inventory;}
    void AddItem(Item* item) {inventory->AddToFront(item);}

    void SetCurrentWeapon(Weapon* weapon);
    void SetCurrentArmor(Armor* armor);

    void SetName(std::string name) {playerName = name;}

    int GetMaxHealth() const {return maxHealth;}
    void IncreaseMaxHealth(int amount) {maxHealth += amount; health += amount;}
    void Heal(int amount) override;

    void RemoveGold(int value) {gold -= value;}
    int GetGold() const {return gold;}
    void AddGold(int value, Game* game);

    std::string GetEntityName() override;
    bool IsPlayer() const override {return true;}
};



#endif //PLAYER_H
