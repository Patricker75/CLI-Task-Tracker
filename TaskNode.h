#ifndef TASKNODE_H
#define TASKNODE_H

#include "Node.h"
#include "LinkedList.h"
#include "Task.h"

#include <string>

struct TaskNode : public Node<int> {
    TaskNode(int date) : Node<int>(date) {
        this->tasks = new LinkedList<Task>();
    };

    std::string FormatDate() {
        int date = this->data;

        int day = date % 100;
        int year = date / 10000;
        date /= 100;
        int month = date % 100;

        std::string output = "";
        if (month < 10) {
            output += "0";
        }
        output += std::to_string(month) + "/";

        if (day < 10) {
            output += "0";
        }
        output += std::to_string(day) + "/" + std::to_string(year);

        return output;
    }

    LinkedList<Task>* tasks;
};

#endif