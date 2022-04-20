#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

template <class T>
class Queue {
private:
    Node<T>* front;
    Node<T>* back;
public:
    Queue<T>() {
        this->front = nullptr;
        this->back = nullptr;
    };

    void Enqueue(T data) {
        Node<T>* temp = new Node<T>(data);

        this->Enqueue(temp);
    };
    void Enqueue(Node<T>* node) {
        if (this->front == nullptr) {
            this->front = node;
            this->back = node;
            return;
        }

        this->back->next = node;
        this->back = node;
    };

    Node<T>* Dequeue() {
        if (this->Empty()) {
            return nullptr;
        }
        Node<T>* temp = this->front;
        this->front = temp->next;
        return temp;
    }  

    bool Empty() {
        return this->front == nullptr;
    }
};

#endif