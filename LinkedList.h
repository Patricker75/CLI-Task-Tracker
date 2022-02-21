#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <string>
#include <iostream>

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

    void Remove(T data, Node<T>* node) {
        if (node->next == nullptr) {
            return;
        }

        if (node->next->data == data) {
            Node<T>* toRemove = node->next;
            node->next = toRemove->next;
            
            if (this->tail == toRemove) {
                this->tail = node;
            }

            delete toRemove;
        }
        else {
            this->Remove(data, node->next);
        }
    }
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

    void Remove(T data) {
        if (this->Empty()) {
            return;
        }
        else if (this->head->data == data) {
            this->head = this->head->next;
            return;
        }

        this->Remove(data, this->head);
    }

    Node<T>* GetHead() {
        return this->head;
    };
    Node<T>* GetTail() {
        return this->tail;
    };

    bool Empty() {
        return this->head == nullptr;
    };
    
    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
        Node<T>* node = list.head;

        while (node != nullptr) {
            os << node->data << " ";
            node = node->next;
        }
        return os;
    };

};

#endif