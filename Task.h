#ifndef TASK_H
#define TASK_H

#include <string>
#include "LinkedList.h"
#include "Date.h"

struct Task {
    Task() {}
    
    Task(std::string name) {
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

    std::string name;
    std::string notes;
    LinkedList<std::string>* tags;
};


#endif