//
// Created by nova on 7/25/25.
//

#include "DungeonGrid.h"
#include "RoomNode.h"
#include "../ADTBaseClasses/Stack.h"
#include <iostream>


DungeonGrid::DungeonGrid(int height, int width, const Game* game) {
    this->height = height;
    this->width = width;

    RoomNode* lastNode = nullptr;
    RoomNode* southNode = nullptr;

    // Holds every node in the current row
    auto* rowQueue = new Queue<RoomNode>();
    // Then, when the end of the row is reached, it's copied over to this, that way nodes can be linked vertically
    Queue<RoomNode>* lastRowQueue = nullptr;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            auto* currentNode = new RoomNode(j, i, width, height, game);
            // The room the player starts in is the bottom left room
            if (i == 1 && j == 1) {
                startRoom = currentNode;
            }
            // The boss room is the opposite corner
            else if (i == height && j == width) {
                bossRoom = currentNode;
            }

            // Stores the current node so it can be used for vertical linking later
            rowQueue->Enqueue(currentNode);

            // Horizontal linking
            currentNode->SetWest(lastNode);
            if (lastNode != nullptr) {
                lastNode->SetEast(currentNode);
            }

            // Vertical linking
            if (lastRowQueue != nullptr) {
                southNode = lastRowQueue->Dequeue();
                currentNode->SetSouth(southNode);
                southNode->SetNorth(currentNode);
            }

            // Traverse to the right
            lastNode = currentNode;
        }

        // Traverse upward then reset
        lastRowQueue = rowQueue;
        rowQueue = new Queue<RoomNode>();
        lastNode = nullptr;
    }

    delete rowQueue;
    delete lastRowQueue;
}

void DungeonGrid::PrintDungeonGrid() const {
    RoomNode* currentNode = startRoom;
    // Holds the start node for each row
    auto* rowStack = new Stack<RoomNode>();

    // Traverse to top left for printing
    while (currentNode->GetNorth() != nullptr) {
        rowStack->Push(currentNode);
        currentNode = currentNode->GetNorth();
    }

    while (true) {
        // Unique characters for each room type,
        // whether the room has the player or has already been cleared takes priority over its type
        if (currentNode->IsPlayerIn()) {
            std::cout << "[@] ";
        }
        else if (currentNode->IsCleared()) {
            std::cout << "[X] ";
        }
        else if (currentNode->GetType() == RoomNode::Type::Boss) {
            std::cout << ">:) ";
        }
        else if (currentNode->GetType() == RoomNode::Type::Normal) {
            std::cout << "[ ] ";
        }
        else if (currentNode->GetType() == RoomNode::Type::Shop) {
            std::cout << "[$] ";
        }

        // This checks if the end of the row has been found
        if (currentNode->GetEast() == nullptr) {
            // This checks if the current node is the bottom right corner
            if (rowStack->IsEmpty()) {
                break;
            }
            // If not, them if moves to the next row and ends the line
            currentNode = rowStack->Pop();
            std::cout << std::endl;
        }
        else {
            currentNode = currentNode->GetEast();
        }
    }

    delete rowStack;
    std::cout << std::endl;
}
