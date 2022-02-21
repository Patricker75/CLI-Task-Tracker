#ifndef TASKNODE_H
#define TASKNODE_H

#include "Node.h"
#include "LinkedList.h"
#include "Task.h"

struct TaskNode : public Node<int> {
    TaskNode(int date) : Node<int>(date) {
        this->tasks = new LinkedList<Task>();
    };

    LinkedList<Task>* tasks;
};

#endif