//
// Created by nova on 7/22/25.
// Node template/base class for singly-linked lists
//

#ifndef SINGLYLINKEDNODE_H
#define SINGLYLINKEDNODE_H

template <typename heldObject> class SinglyLinkedNode {
protected:
    heldObject* object;
    SinglyLinkedNode* next;
public:
    explicit SinglyLinkedNode(heldObject* object, SinglyLinkedNode* next = nullptr)
        : object(object), next(next) {}

    virtual ~SinglyLinkedNode() = default;

    SinglyLinkedNode* GetNext() const {return next;}
    heldObject* GetObject() const {return object;}
    void SetNext(SinglyLinkedNode* next) {this->next = next;}
};



#endif //SINGLYLINKEDNODE_H
