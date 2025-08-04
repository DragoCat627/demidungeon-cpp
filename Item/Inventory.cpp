//
// Created by nova on 7/27/25.
//

#include "Inventory.h"
#include "Item.h"

#include <iostream>
#include <iomanip>

class Item;

// Returns true if two values should be swapped for a given sorting order
bool Inventory::ShouldSwap(int valueA, int valueB, SortOrder order) {
    switch (order) {
        case SortOrder::Ascending:
            return valueA > valueB;
        case SortOrder::Descending:
            return valueA < valueB;
        default:
            return false;
    }
}

// Determines if two items are in the correct order for a given parameter and sorting order
bool Inventory::NotInCorrectOrder(Item *a, Item *b, SortParameter parameter, SortOrder order) {
    switch (parameter) {
        case SortParameter::ID:
            return ShouldSwap(a->GetID(), b->GetID(), order);
        case SortParameter::Value:
            return ShouldSwap(a->GetValue(), b->GetValue(), order);
        case SortParameter::Type:
            return ShouldSwap(static_cast<int>(a->GetType()), static_cast<int>(b->GetType()), order);
        case SortParameter::Effect:
            return ShouldSwap(static_cast<int>(a->GetEffect()), static_cast<int>(b->GetEffect()), order);
        case SortParameter::Damage:
            return ShouldSwap(a->GetDamage(order), b->GetDamage(order), order);
        case SortParameter::Defense:
            return ShouldSwap(a->GetDefense(order), b->GetDefense(order), order);
        case SortParameter::Potency:
            return ShouldSwap(a->GetPotency(order), b->GetPotency(order), order);
        case SortParameter::Duration:
            return ShouldSwap(a->GetDuration(order), b->GetDuration(order), order);
        default:
            return false;
    }
}

// Bubble sort algorithm that can sort by any of the given parameters in either ascending or descending order
void Inventory::SortInventory(SortParameter parameter, SortOrder order) {
    if (this->IsEmpty()) {
        return;
    }
    bool swapped = true;
    while (swapped) {
        swapped = false;
        DoublyLinkedNode<Item>* current = front;
        while (current->GetNext() != nullptr) {
            Item* a = current->GetObject();
            Item* b = current->GetNext()->GetObject();
            if (NotInCorrectOrder(a, b, parameter, order)) {
                Swap(current, current->GetNext());
                swapped = true;
            }
            current = current->GetNext();
        }
    }
}

void Inventory::PrintInventory() {
    if (this->IsEmpty()) {
        std::cout << "You have no items" << std::endl;
        return;
    }

    const int width = 12;

    std::cout << std::left;
    std::cout << std::setw(width) << "ID Number:"
              << std::setw(width) << "Type:"
              << std::setw(width) << "Effect:"
              << std::setw(width) << "Value:"
              << std::setw(width) << "Damage:"
              << std::setw(width) << "Defense:"
              << std::setw(width) << "Potency:"
              << std::setw(width) << "Duration:"
              << std::endl;

    DoublyLinkedNode<Item>* currentNode = this->GetFront();
    Item* currentItem = currentNode->GetObject();
    while (true) {
        std::cout << std::setw(width) << currentItem->GetID()
                  << std::setw(width) << currentItem->GetTypeAsString()
                  << std::setw(width) << currentItem->GetEffectAsString()
                  << std::setw(width) << currentItem->GetValue()
                  << std::setw(width) << currentItem->GetDamage()
                  << std::setw(width) << currentItem->GetDefense()
                  << std::setw(width) << currentItem->GetPotency()
                  << std::setw(width) << currentItem->GetDuration()
                  << std::endl;
        currentNode = currentNode->GetNext();
        if (currentNode == nullptr) {
            return;
        }
        currentItem = currentNode->GetObject();
    }
}

bool Inventory::HasItemWithID(int id) {
    DoublyLinkedNode<Item>* currentNode = this->GetFront();
    while (currentNode != nullptr) {
        if (currentNode->GetObject()->GetID() == id) {
            return true;
        }
        currentNode = currentNode->GetNext();
    }
    return false;
}

Item* Inventory::GetItemWithID(int id) {
    DoublyLinkedNode<Item>* currentNode = this->GetFront();
    while (currentNode != nullptr) {
        if (currentNode->GetObject()->GetID() == id) {
            return currentNode->GetObject();
        }
        currentNode = currentNode->GetNext();
    }
    return nullptr;
}

Item* Inventory::RemoveItemWithID(int id) {
    DoublyLinkedNode<Item>* currentNode = this->GetFront();
    while (currentNode != nullptr) {
        if (currentNode->GetObject()->GetID() == id) {
            return Remove(currentNode);
        }
        currentNode = currentNode->GetNext();
    }
    return nullptr;
}

