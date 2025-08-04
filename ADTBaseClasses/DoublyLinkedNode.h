//
// Created by nova on 7/22/25.
// Node template class for doubly-linked lists
//

#ifndef DOUBLYLINKEDNODE_H
#define DOUBLYLINKEDNODE_H



template <typename heldObject> class DoublyLinkedNode {
protected:
    heldObject* object;
    DoublyLinkedNode* next;
    DoublyLinkedNode* prev;

public:
    explicit DoublyLinkedNode(heldObject* object, DoublyLinkedNode* next = nullptr, DoublyLinkedNode* prev = nullptr)
        : object(object), next(next), prev(prev) {}
    ~DoublyLinkedNode() {}

    DoublyLinkedNode* GetNext() {return next;}
    DoublyLinkedNode* GetPrev() {return prev;}
    heldObject* GetObject() {return object;}
    void SetObject(heldObject* object) {this->object = object;}
    void SetNext(DoublyLinkedNode* next) {this->next = next;}
    void SetPrev(DoublyLinkedNode* prev) {this->prev = prev;}
};



#endif //DOUBLYLINKEDNODE_H
