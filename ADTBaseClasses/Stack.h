//
// Created by nova on 7/29/25.
// Stack ADT template class for the traversal and printing of the grid
//

#ifndef STACK_H
#define STACK_H

#include "SinglyLinkedNode.h"

template <typename heldObject> class Stack {
protected:
    SinglyLinkedNode<heldObject>* top;
    int size;
public:
    Stack() : top(nullptr), size(0) {}
    virtual ~Stack();

    bool IsEmpty() const {return size == 0;}
    int GetSize() const {return size;}

    void Push(heldObject* object);
    heldObject* Pop();
    heldObject* Peek();
};

template<typename heldObject> Stack<heldObject>::~Stack() {
    while (!IsEmpty()) {
        Pop();
    }
}

template<typename heldObject> void Stack<heldObject>::Push(heldObject* object) {
    auto* newNode = new SinglyLinkedNode<heldObject>(object);
    newNode->SetNext(top);
    top = newNode;
    size++;
}

template<typename heldObject> heldObject* Stack<heldObject>::Pop() {
    if (IsEmpty()) {
        return nullptr;
    }

    SinglyLinkedNode<heldObject>* temp = top;
    heldObject* object = top->GetObject();

    top = top->GetNext();
    delete temp;
    size--;

    if (size == 0) {
        top = nullptr;
    }

    return object;
}

template<typename heldObject> heldObject* Stack<heldObject>::Peek() {
    if (IsEmpty()) {
        return nullptr;
    }
    return top->GetObject();
}

#endif //STACK_H
