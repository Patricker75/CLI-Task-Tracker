#ifndef NODE_H
#define NODE_H

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

};

#endif