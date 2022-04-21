#ifndef TAGSTREE_H
#define TAGSTREE_H

#include "Task.h"
#include "LinkedList.h"

struct TagNode {
    TagNode(int key) {
        this->key = key;
        this->tasks = new LinkedList<Task*>();

        this->left = nullptr;
        this->right = nullptr;
    }
    
    int key;
    LinkedList<Task*>* tasks;

    TagNode* left;
    TagNode* right;
};

class TagsTree {
private:
    TagNode* root;

    TagNode* Delete(int key, TagNode* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            return this->Delete(key, node->left);
        }
        else if (key > node->key) {
            return this->Delete(key, node->right);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;

                return nullptr;
            }
            else if (node->left != nullptr && node->right != nullptr) {
                TagNode* successor = node->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }
                node->key = successor->key;
                node->tasks = successor->tasks;

                node->right = this->Delete(successor->key, node->right);
                return node;                
            }
            else if (node->left != nullptr) {
                TagNode* temp = node->left;
                delete node;
                return temp;
            }
            else if (node->right != nullptr) {
                TagNode* temp = node->right;
                delete node;
                return temp;
            }
        }
    }
public:
    TagsTree() {
        this->root = nullptr;
    }

    void Insert(int key, Task* t) {
        if (this->root == nullptr) {
            this->root = new TagNode(key);
            this->root->tasks->Insert(t);

            return;
        }

        TagNode* current = this->root;
        while (current != nullptr) {
            if (key == current->key) {
                current->tasks->Insert(t);

                return;
            }
            else if (key < current->key) {
                if (current->left == nullptr) {
                    current->left = new TagNode(key);
                    current->left->tasks->Insert(t);

                    return;
                }

                current = current->left;
            }
            else {
                if (current->right == nullptr) {
                    current->right = new TagNode(key);
                    current->right->tasks->Insert(t);

                    return;
                }
            }
        }
    }
    
    void Remove(Task* t) {
        TagNode* target = this->Search(t->dueDate);

        target->tasks->Delete(t);

        if (target->tasks->Empty()) {
            this->root = this->Delete(t->dueDate, this->root);
        }
    }

    TagNode* Search(int key) {
        TagNode* current = this->root;

        while (current != nullptr && current->key != key) {
            if (key < current->key) {
                current = current->left;
            }
            else if (key > current->key) {
                current = current->right;
            }
        }

        return current;
    }

    TagNode* GetRoot() {
        return this->root;
    }

};

#endif