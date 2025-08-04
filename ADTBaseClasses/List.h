//
// Created by nova on 7/22/25.\
// List ADT template/base class for the inventory
// Implemented using a doubly-linked list
//

#ifndef LIST_H
#define LIST_H
#include "DoublyLinkedNode.h"


template <typename heldObject> class List {
protected:
    DoublyLinkedNode<heldObject>* front;
    DoublyLinkedNode<heldObject>* rear;
    int size;
public:
    List() : front(nullptr), rear(nullptr), size(0) {}
    ~List();

    // Overloaded = operator 1/3
    List& operator=(const List& other);

    void AddToFront(heldObject* object);
    void AddToRear(heldObject* object);
    heldObject* RemoveFromFront();
    heldObject* RemoveFromRear();

    heldObject* Remove(DoublyLinkedNode<heldObject>* node);
    bool Contains(heldObject* object);

    void Swap(DoublyLinkedNode<heldObject>* a, DoublyLinkedNode<heldObject>* b) {
        heldObject* temp = a->GetObject();
        a->SetObject(b->GetObject());
        b->SetObject(temp);
    }

    bool IsEmpty() const {return size == 0;}
    int GetSize() const {return size;}
    DoublyLinkedNode<heldObject>* GetFront() {return front;}
    DoublyLinkedNode<heldObject>* GetRear() {return rear;}
};


template<typename heldObject> List<heldObject>::~List() {
    while (!IsEmpty()) {
        RemoveFromFront();
    }
}

template<typename heldObject> List<heldObject>& List<heldObject>::operator=(const List& other) {
    if (this == &other)
        return *this;

    while (!IsEmpty()) {
        RemoveFromFront();
    }

    DoublyLinkedNode<heldObject>* current = other.front;
    while (current) {
        AddToRear(current->GetObject());
        current = current->GetNext();
    }

    return *this;
}

template<typename heldObject> void List<heldObject>::AddToFront(heldObject* object) {
    DoublyLinkedNode<heldObject>* newNode = new DoublyLinkedNode<heldObject>(object, front, nullptr);
    if (front != nullptr) {
        front->SetPrev(newNode);
    }
    else {
        rear = newNode;
    }
    front = newNode;
    size++;
}

template<typename heldObject> void List<heldObject>::AddToRear(heldObject* object) {
    DoublyLinkedNode<heldObject>* newNode = new DoublyLinkedNode<heldObject>(object, nullptr, rear);
    if (rear != nullptr) {
        rear->SetNext(newNode);
    }
    else {
        front = newNode;
    }
    rear = newNode;
    size++;
}

template<typename heldObject> heldObject* List<heldObject>::RemoveFromFront() {
    if (IsEmpty()) {
        return nullptr;
    }
    DoublyLinkedNode<heldObject>* temp = front;
    front = front->GetNext();
    if (front != nullptr) {
        front->SetPrev(nullptr);
    }
    else {
        rear = nullptr;
    }
    heldObject* object = temp->GetObject();
    delete temp;
    size--;
    return object;
}

template<typename heldObject> heldObject* List<heldObject>::RemoveFromRear() {
    if (IsEmpty()) {
        return nullptr;
    }
    DoublyLinkedNode<heldObject>* temp = rear;
    rear = rear->GetPrev();
    if (rear != nullptr) {
        rear->SetNext(nullptr);
    }
    else {
        front = nullptr;
    }
    heldObject* object = temp->GetObject();
    delete temp;
    size--;
    return object;
}

template<typename heldObject> heldObject* List<heldObject>::Remove(DoublyLinkedNode<heldObject>* node) {
    if (!node || IsEmpty()) return nullptr;

    if (node == front) {
        return RemoveFromFront();
    }
    if (node == rear) {
        return RemoveFromRear();
    }

    DoublyLinkedNode<heldObject>* prev = node->GetPrev();
    DoublyLinkedNode<heldObject>* next = node->GetNext();

    if (prev) {
        prev->SetNext(next);
    }
    if (next) {
        next->SetPrev(prev);
    }

    heldObject* object = node->GetObject();
    delete node;
    size--;
    return object;
}

template<typename heldObject> bool List<heldObject>::Contains(heldObject* object) {
    for (DoublyLinkedNode<heldObject>* current = front; current != nullptr; current = current->GetNext()) {
        if (current->GetObject() == object) return true;
    }
    return false;
}


#endif //LIST_H
