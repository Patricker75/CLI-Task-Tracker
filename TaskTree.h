#ifndef TASKTREE_H
#define TASKTREE_H

#include "Task.h"
#include "LinkedList.h"

struct TNode {
    TNode(int key) {
        this->key = key;
        this->tasks = new LinkedList<Task>();

        this->left = nullptr;
        this->right = nullptr;
    }

    int key;
    LinkedList<Task>* tasks;
    TNode* left;
    TNode* right;
};

class TaskTree {
private:
    TNode* root;

    TNode* Delete(int key, TNode* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = this->Delete(key, node->left);
            return node;
        }
        else if (key > node->key) {
            node->right = this->Delete(key, node->right);
            return node;
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;

                return nullptr;
            }
            else if (node->left != nullptr && node->right != nullptr) {
                TNode* successor = node->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }
                node->key = successor->key;
                node->tasks = successor->tasks;

                node->right = this->Delete(successor->key, node->right);
                return node;
            }
            else if (node->left != nullptr) {
                TNode* temp = node->left;
                delete node;
                return temp;
            }
            else if (node->right != nullptr) {
                TNode* temp = node->right;
                delete node;
                return temp;
            }
        }
    }
public:
    TaskTree() {
        this->root = nullptr;
    };

    Task* Insert(int key, Task task) {
        TNode* node = this->Search(key);

        if (node != nullptr) {
            return node->tasks->Insert(task);
        }

        node = new TNode(key);
        Task* ptr = node->tasks->Insert(task);
        if (this->root == nullptr) {
            this->root = node;

            return ptr;
        }

        TNode* current = this->root;
        while (current != nullptr) {
            if (node->key < current->key) {
                if (current->left == nullptr) {
                    current->left = node;
                    break;
                }

                current = current->left;
            }
            else if (node->key > current->key) {
                if (current->right == nullptr) {
                    current->right = node;
                    break;
                }

                current = current->right;
            }
        }

        return ptr;
    }

    Task* Insert(Task task) {
        int key = task.dueDate;
        TNode* node = this->Search(key);

        if (node != nullptr) {
            return node->tasks->Insert(task);
        }

        node = new TNode(key);
        Task* ptr = node->tasks->Insert(task);
        if (this->root == nullptr) {
            this->root = node;

            return ptr;
        }

        TNode* current = this->root;
        while (current != nullptr) {
            if (node->key < current->key) {
                if (current->left == nullptr) {
                    current->left = node;
                    break;
                }

                current = current->left;
            }
            else if (node->key > current->key) {
                if (current->right == nullptr) {
                    current->right = node;
                    break;
                }

                current = current->right;
            }
        }

        return ptr;
    }

    TNode* Search(int key) {
        if (this->root == nullptr) {
            return nullptr;
        }

        TNode* current = this->root;

        while (current != nullptr && key != current->key) {
            if (key < current->key) {
                current = current->left;
            }
            else if (key > current->key) {
                current = current->right;
            }
        }

        return current;
    }
    
    void Delete(int key) {
        this->root = this->Delete(key, this->root);
    }

    TNode* GetRoot() {
        return this->root;
    }

    bool Empty() {
        return this->root == nullptr;
    }
};

#endif