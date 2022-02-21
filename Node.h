#ifndef NODE_H
#define NODE_H

#include <iostream>

template <class T>
struct Node {
    T data;

    Node<T>* next;
    Node<T>* left;
    Node<T>* right;

    Node<T>(T data) {
        this->data = data;

        this->next = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    };

    friend std::ostream& operator<< (std::ostream& os, const Node<T>& node) {
        os << node.data;
        return os;
    }

};

#endif