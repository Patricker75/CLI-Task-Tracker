#ifndef TASK_H
#define TASK_H

#include <string>

#include "LinkedList.h"

struct Task {
public:
    Task() {};

    Task(std::string name, int dueDate) {
        this->name = name;
        this->dueDate = dueDate;

        this->notes = "";
        this->tags = new LinkedList<std::string>();
    };

    Task(std::string name, int year, int month, int day) {
        this->name = name;
        this->dueDate = year * 10000 + month * 100 + day;

        this->tags = new LinkedList<std::string>();
    }
    
    std::string name;
    int dueDate;

    LinkedList<std::string>* tags;
    std::string notes;

    friend bool operator==(const Task& task1, const Task& task2) {
        return task1.name == task2.name;
    }

    friend bool operator!=(const Task& task1, const Task& task2) {
        return !(task1.name == task2.name);
    }
};

#endif