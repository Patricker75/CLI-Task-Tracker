#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>
#include "LinkedList.h"
#include "Date.h"

struct Task {
    Task() {}
    
    Task(std::string name, int due) {
        this->name = name;
        this->dueDate = due;

        this->notes = "";
        this->tags = new LinkedList<std::string>();
    }

    Task(std::string name, int due, std::string notes) {
        this->name = name;
        this->dueDate = due;
        this->notes = notes;

        this->tags = new LinkedList<std::string>();
    }

    Task(std::string name, int due, std::string notes, LinkedList<std::string>* tags) {
        this->name = name;
        this->dueDate = due;
        this->notes = notes;
        this->tags = tags;
    }

    Task(const Task& task) {
        this->name = task.name;
        this->dueDate = task.dueDate;
        this->notes = task.notes;
        this->tags = task.tags;
    }

    friend std::ostream& operator<< (std::ostream& os, const Task& task) {
        os << task.name;
        return os;
    }
    friend bool operator==(const Task& t1, const Task& t2) {
        return t1.name == t2.name;
    }

    std::string name;
    std::string notes;
    LinkedList<std::string>* tags;
    int dueDate;
};


#endif