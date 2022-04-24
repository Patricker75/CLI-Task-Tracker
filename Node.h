#ifndef NODE_H
#define NODE_H

template <class T>
struct Node {
public:
    Node<T>(T data) {
        this->data = data;

        this->next = nullptr;
        this->prev = nullptr;
    };
    
    T data;

    Node<T>* next;
    Node<T>* prev;
};

#endif