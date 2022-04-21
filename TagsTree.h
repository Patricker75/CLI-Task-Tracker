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
    
    TagNode* GetRoot() {
        return this->root;
    }

};

#endif