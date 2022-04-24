#ifndef STACK_H
#define STACK_H

#include "Node.h"

template <class T>
class Stack {
private:
    Node<T>* top;
public:
    Stack() {
        this->top = nullptr;
    };

    void Push(T data) {
        Node<T>* temp = new Node<T>(data);

        if (this->top == nullptr) {
            this->top = temp;
            return;
        }

        temp->next = this->top;
    }

    T Pop() {
        Node<T>* temp = this->top;
        this->top = temp->next;
        return temp->data;
    }

    T Peek() {
        return this->top->data;
    }

    bool Empty() {
        return this->top == nullptr;
    }    
};

#endif