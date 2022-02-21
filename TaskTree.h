#ifndef TASKTREE_H
#define TASKTREE_H

#include "TaskNode.h"

class TaskTree {
private:
    TaskNode* root;

    Node<int>* Search(int date, Node<int>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        
        if (date == node->data) {
            return static_cast<TaskNode*>(node);
        }

        if (date < node->data) {
            return Search(date, node->left);
        }
        return Search(date, node->right);
    }

    void Insert(Node<int>* currentNode, TaskNode* toAdd) {
        if (toAdd->data < currentNode->data) {
            if (currentNode->left == nullptr) {
                currentNode->left = toAdd;
            }
            else {
                this->Insert(currentNode->left, toAdd);
            }
        }
        else if (toAdd->data > currentNode->data) {
            if (currentNode->right == nullptr) {
                currentNode->right = toAdd;
            }
            else {
                this->Insert(currentNode->right, toAdd);
            }
        }
    }
public:
    TaskTree() {
        this->root = nullptr;
    };

    void Insert(int date, const Task& task) {
        TaskNode* targetNode = this->Search(date);

        if (targetNode == nullptr) {
            targetNode = new TaskNode(date);
        }
        targetNode->tasks->Add(task);

        if (this->root == nullptr) {
            this->root = targetNode;
            return;
        }
    }

    TaskNode* Search(int date) {
        if (this->root == nullptr) {
            return nullptr;
        }

        Node<int>* temp = this->Search(date, this->root);
        return static_cast<TaskNode*>(temp);
    }
    
};

#endif