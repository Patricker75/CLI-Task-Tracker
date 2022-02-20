#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <string>

template <class T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

    std::string ToString(Node<T>* node) {
        std::string output = "";
        if (node == nullptr) {
            return output;
        }
        output += std::to_string(node->data) + " " + this->ToString(node->next);
        return output;
    };
public:
    LinkedList<T>() {
        this->head = nullptr;
        this->tail = nullptr;
    };
    
    void Add(T data) {
        Node<T>* temp = new Node<T>(data);

        this->Add(temp);
    };
    void Add(Node<T>* node) {
        if (this->head == nullptr) {
            this->head = node;
            this->tail = node;
            return;
        }

        this->tail->next = node;
        this->tail = node;
    };

    Node<T>* GetHead() {
        return this->head;
    };
    Node<T>* GetTail() {
        return this->tail;
    };

    bool Empty() {
        return this->head == nullptr;
    };
    std::string ToString() {
        return this->ToString(this->head);
    };

};

#endif