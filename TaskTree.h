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

    std::string GetAllTasks(TaskNode* node) {
        std::string returnData = "";
        if (node == nullptr) {
            return "";
        }

        returnData += this->GetAllTasks(static_cast<TaskNode*>(node->left));
        
        returnData += node->FormatDate() + "\n";

        Node<Task>* curr = node->tasks->GetHead();
        while (curr != nullptr) {
            returnData += "\t" + curr->data.name + "\n";
            curr = curr->next;
        }
        returnData += "\n";

        returnData += this->GetAllTasks(static_cast<TaskNode*>(node->right));

        return returnData;
    }
public:
    TaskTree() {
        this->root = nullptr;
    };

    void Insert(const Task& task) {
        TaskNode* targetNode = this->Search(task.dueDate);

        if (targetNode == nullptr) {
            targetNode = new TaskNode(task.dueDate);
        }
        targetNode->tasks->Add(task);

        if (this->root == nullptr) {
            this->root = targetNode;
            return;
        }

        this->Insert(this->root, targetNode);
    }

    TaskNode* Search(int date) {
        if (this->root == nullptr) {
            return nullptr;
        }

        Node<int>* temp = this->Search(date, this->root);
        return static_cast<TaskNode*>(temp);
    }

    Task* SearchTask(Task t) {
        LinkedList<Task>* list = this->Search(t.dueDate)->tasks;

        Node<Task>* node = list->GetHead();
        while (node != nullptr) {
            if (t == node->data) {
                return &node->data;
            }
            node = node->next;
        }

        return nullptr;
    }
    
    std::string GetAllTasks() {
        return this->GetAllTasks(this->root);
    }

    TaskNode* GetRoot() {
        return this->root;
    }
};

#endif