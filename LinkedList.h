#ifndef LinkedList_H
#define LinkedList_H

#include "Node.h"

template <class T>
class LinkedList {
private:
    Node<T>* head;
    int length;
public:
    LinkedList<T>() {
        this->head = nullptr;
        this->length = 0;
    };

    T* Insert(T data) {
        Node<T>* temp = new Node<T>(data);
        this->length++;
        if (this->head == nullptr) {
            this->head = temp;

            return &temp->data;
        }

        Node<T>* current = this->head;
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = temp;
        temp->prev = current;
        return &temp->data;
    }

    void Delete(T data) {
        if (this->Empty()) {
            return;
        }

        Node<T>* current = this->head;

        while (current != nullptr && current->data != data) {
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }

        this->length--;
        if (current == this->head) {
            this->head = current->next;
        }

        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }
        current->next = current->prev;
    }

    Node<T>* Search(T data) {
        Node<T>* current = this->head;

        while (current != nullptr) {
            if (current->data == data) {
                break;
            }
        }
        
        return current;
    }

    bool Empty() {
        return this->head == nullptr;
    }

    Node<T>* GetHead() {
        return this->head;
    }

    int GetLength() {
        return this->length;
    }
};

#endif