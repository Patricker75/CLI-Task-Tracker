#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>
#include "LinkedList.h"
#include "Date.h"

struct Task {
    Task() {}
    
    Task(const std::string& name) {
        this->name = name;
        this->notes = "";
        this->tags = new LinkedList<std::string>();
    }

    Task(std::string name, std::string notes) {
        this->name = name;
        this->notes = notes;
        this->tags = new LinkedList<std::string>();
    }

    Task(std::string name, std::string notes, LinkedList<std::string>* tags) {
        this->name = name;
        this->notes = notes;
        this->tags = tags;
    }

    Task(const Task& task) {
        this->name = task.name;
        this->notes = task.notes;
        this->tags = task.tags;
    }

    friend std::ostream& operator<< (std::ostream& os, const Task& task) {
        os << task.name;
        return os;
    }

    std::string name;
    std::string notes;
    LinkedList<std::string>* tags;
};


#endif