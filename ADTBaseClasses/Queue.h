//
// Created by nova on 7/22/25.
// Queue ADT template/base class for keeping track of turn order in combat, handling status effects, and for the construction of the grid
// Implemented using a singly-linked list
//

#ifndef QUEUE_H
#define QUEUE_H

#include "SinglyLinkedNode.h"

template <typename heldObject> class Queue {
protected:
    SinglyLinkedNode<heldObject>* front;
    SinglyLinkedNode<heldObject>* rear;
    int size;
public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    virtual ~Queue();
    // Overloaded = operator 2/3
    Queue& operator=(Queue* other);

    bool IsEmpty() const {return front == nullptr;}
    int GetSize() const {return size;}

    virtual void Enqueue(heldObject* object);
    heldObject* Dequeue();
    heldObject* Peek();
    void Clear();

    SinglyLinkedNode<heldObject>* GetFront() {return front;}
};

template<typename heldObject> Queue<heldObject>::~Queue() {
    while (!IsEmpty()) {
        Dequeue();
    }
}

template<typename heldObject> Queue<heldObject>& Queue<heldObject>::operator=(Queue* other) {
    if (this == other) {
        return *this;
    }

    this->Clear();

    SinglyLinkedNode<heldObject>* current = other.front;
    while (current) {
        Enqueue(current->GetObject());
        current = current->GetNext();
    }

    return *this;
}

template<typename heldObject> void Queue<heldObject>::Enqueue(heldObject* object) {
    auto* newNode = new SinglyLinkedNode(object);
    if (IsEmpty()) {
        front = newNode;
        rear = newNode;
    }
    else {
        rear->SetNext(newNode);
        rear = newNode;
    }
    size++;
}

template<typename heldObject> heldObject* Queue<heldObject>::Dequeue() {
    if (IsEmpty()) {
        return nullptr;
    }

    SinglyLinkedNode<heldObject>* temp = front;
    heldObject* object = front->GetObject();

    front = front->GetNext();
    delete temp;
    size--;

    if (size == 0) {
        front = nullptr;
        rear = nullptr;
    }

    return object;
}

template<typename heldObject> heldObject* Queue<heldObject>::Peek() {
    if (IsEmpty()) {
        return nullptr;
    }
    return front->GetObject();
}

template<typename heldObject> void Queue<heldObject>::Clear() {
    while (!IsEmpty()) {
        Dequeue();
    }
}


#endif //QUEUE_H
